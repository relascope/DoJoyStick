//
// Created by guru on 11.10.23.
//

#include "JoystickMidiMediator.h"
#include "dojoysticklooper.hpp"
#include "glue.h"
#include "jsevent.h"
#include "midijack.h"
#include <iostream>
#include <linux/joystick.h>

JoystickMidiMediator::JoystickMidiMediator(const std::string joystickDeviceName) : jsEvents(joystickDeviceName) {
    jsEvents.setEventHandler(&event_handler, &jsEvents);
    setup_jack(&jrb, DEFAULT_RB_SIZE);
}

void JoystickMidiMediator::event_handler(struct js_event event, JsEvents::CLICK_TYPE t, void *__this) {
    std::cout << "===============EVENT===========" << std::endl;
    JsEvents::jsdiag(event);
    JsEvents::printType(t);

    char msg[3];
    msg[2] = 111;
    msg[1] = 0x3c;
    msg[0] = event.value == 1 ? 0x90 : 0x80;

    ((JoystickMidiMediator *) (__this))->sendMidiMessage(msg, sizeof(msg));
}

void JoystickMidiMediator::run_main_loop() {
    jsEvents.js_event_loop();
}

void JoystickMidiMediator::sendMidiMessage(const char *msg, size_t size) {
    if (size == 0) return;

    struct midi_msg midi;
    memset(&midi, 0, sizeof(midi));

    for (size_t i = 0; i < size && i < MAX_MIDI_MSG; i++) {
        midi.msg[i] = msg[i];
    }

    midi.size = size;

    if (jack_ringbuffer_write_space(jrb) < sizeof(midi)) {
        //	  fprintf(stderr, "midi message will not fit in ringbuffer\n");
        throw "midi message will not fit in ringbuffer\n";
    }

    if ((jack_ringbuffer_write(jrb, (const char *) (void *) &midi, sizeof(midi))) != sizeof(midi)) {
        throw "error writing midi to ringbuffer";
    }
}

//     for (int i=0; i < size && ___PAIRP(lst) && i < MAX_MIDI_MSG; ++i) {
//	  ___SCMOBJ scm_int = ___CAR(lst);
//	  uint8_t c_int;
//	  ___SCMOBJ ___err;
//	  ___err = ___EXT(___SCMOBJ_to_U8) (scm_int, &c_int, size);
//	  if (___err != ___FIX(___NO_ERR)) {
//            return ___err;
//	  }
//	  midi.msg[i] = c_int;
//	  lst = ___CDR(lst);
//     }
//     midi.size = size;
////     fprintf(stderr, "m1: %x m2: %x m3: %x\n", midi.msg[0], midi.msg[1], midi.msg[2]);
//
//
//
//     if (jack_ringbuffer_write_space(jrb) < sizeof(midi)) {
////	  fprintf(stderr, "midi message will not fit in ringbuffer\n");
//	  return -1;
//     }
//
//     if(jack_ringbuffer_write(jrb, (void*) &midi, sizeof(midi)) != sizeof(midi))
//	  return -1;
//     return 0;
//}
