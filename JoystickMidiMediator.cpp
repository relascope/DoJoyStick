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


char velocity = 111;

void JoystickMidiMediator::event_handler(JoystickEvent event, void *__this) {
    std::cout << "===============EVENT===========" << std::endl;

    event.print();

    // Button #4,5,6,7 are A,B,C,D on Joystick Microsoft Microsoft SideWinder Precision Pro
    // for the time just hardcode to be a good left foot pedal for x42 Black Pearl drumkit
    
    if (event.getButtonNumber() == 2) {
        if (event.getNativeEvent().value < 0) {
            velocity--;
        } else if (event.getNativeEvent().value > 0) {
            velocity++;
        }

        // prevent overflow and underflow
        velocity %= 128;
        return;
    }

    char msg[3];
    msg[0] = event.isButtonDown() == 1 ? 0x90 : 0x80;
    msg[2] = velocity;

    switch (event.getButtonNumber()) {
        case 4:
            msg[1] = 0x31;// 49;// C# 3 Crash Cymbal 1
            break;
        case 5:
            msg[1] = 0x30;//48; // C3 Swish HiHat
            break;
        case 6:
            msg[1] = 0x26;//38; // D2 Snare Ctr.
            break;
        case 7:
            msg[1] = 0x29;//41; // F2 FLoor Tom Ctr.
            break;
        default:
            return;
    }
    (static_cast<JoystickMidiMediator *>(__this))->sendMidiMessage(msg, sizeof(msg));
}

JoystickMidiMediator::JoystickMidiMediator(const std::string joystickDeviceName) : jsEvents(joystickDeviceName) {
    jsEvents.setEventHandler(&event_handler, &jsEvents);
    setup_jack(&jrb, DEFAULT_RB_SIZE);
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
