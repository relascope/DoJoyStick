//
// Created by guru on 11.10.23.
//

#include "JoystickMidiMediator.h"
#include "dojoysticklooper.hpp"
#include "glue.h"
#include "joystick-gateway.h"
#include "midijack.h"
#include <iostream>
#include <linux/joystick.h>


char velocity = 111;

void JoystickMidiMediator::event_handler(JoystickEvent event, void *joystickMediator) {
    std::cout << "===============EVENT===========" << std::endl;
    event.print();
    JoystickMidiMediator *_this = (static_cast<JoystickMidiMediator *>(joystickMediator));

    // Button #4,5,6,7 are A,B,C,D on Joystick Microsoft Microsoft SideWinder Precision Pro
    // Button "ArrowUp" is 8
    // for the time just hardcode to be a good left foot pedal for x42 Black Pearl drumkit

    // axis number 2 not good for velocity change
//    if (event.getButtonNumber() == 2) {
//        if (event.getNativeEvent().value < 0) {
//            velocity = std::max(velocity - 1, 0);
//        } else if (event.getNativeEvent().value > 0) {
//            velocity = std::min(velocity + 1, 128);
//        }
//
//        std::cout << "================================================================" << '\n';
//        std::cout << "velocity: " << velocity << std::endl;
//
//        return;
//    }


    switch (event.getButtonNumber()) {
        char msg[3];
        case 4:
            msg[0] = event.isButtonDown() == 1 ? 0x90 : 0x80;
            msg[2] = velocity;
            msg[1] = 0x31;// 49;// C# 3 Crash Cymbal 1
            _this->sendMidiMessage(msg, sizeof(msg));
            break;
        case 5:
            msg[0] = event.isButtonDown() == 1 ? 0x90 : 0x80;
            msg[2] = velocity;
            msg[1] = 0x30;//48; // C3 Swish HiHat
            _this->sendMidiMessage(msg, sizeof(msg));
            break;
        case 6:
            msg[0] = event.isButtonDown() == 1 ? 0x90 : 0x80;
            msg[2] = velocity;
            msg[1] = 0x24;//C2 (36) hydrogen GM Rock Kit groovy Base//
            _this->sendMidiMessage(msg, sizeof(msg));

            msg[1] = 0x29;// F2 41 Floor Tom Ctr.
            msg[2] = (velocity - 42) % 128;
            _this->sendMidiMessage(msg, sizeof(msg));
            //            msg [1] = 0x26; // 0x26;//38; // D2 Snare Ctr.
            break;
        case 7:
            msg[0] = event.isButtonDown() == 1 ? 0x90 : 0x80;
            msg[2] = velocity;
            msg[1] = 0x29;//41; // F2 FLoor Tom Ctr.
            _this->sendMidiMessage(msg, sizeof(msg));
            break;
        case 8:
            msg[0] = event.isButtonDown() == 1 ? 0x90 : 0x80;
            msg[2] = velocity;
            msg[1] = 0x24;//C2 (36) hydrogen GM Rock Kit groovy Base//
            _this->sendMidiMessage(msg, sizeof(msg));

            msg[1] = 0x29;// F2 41 Floor Tom Ctr.
            msg[2] = (velocity - 42) % 128;
            _this->sendMidiMessage(msg, sizeof(msg));
            break;
        default:
            return;
    }
}

JoystickMidiMediator::JoystickMidiMediator(const std::string &joystickDeviceName) : jsEvents(joystickDeviceName) {
    jsEvents.setEventHandler(&event_handler, &jsEvents);
    setup_jack(&jrb, DEFAULT_RB_SIZE);
}

void JoystickMidiMediator::run_main_loop() {
    jsEvents.js_event_loop();
}

void JoystickMidiMediator::sendMidiMessage(const char *msg, size_t size) {
    if (size == 0) return;

    printMidiMessage(msg, size);
    printMidiMessage(msg, size, false);

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
void JoystickMidiMediator::printMidiMessage(const char *msg, size_t size, bool hex) {
    std::cout << "======MIDI Event " << (hex ? "HEX" : "DEC");
    std::cout << "===========================================================" << '\n';

    if (hex) {
        printf("%x\n", msg);
    } else {
        printf("%d\n", msg);
    }

    for (size_t i = 0; i < size; i++) {
        std::cout << "pos" << i << ":";
        if (hex) {
            std::cout << std::hex << static_cast<int>(msg[i]);
        } else {
            std::cout << static_cast<int>(msg[i]);
        }
        std::cout << '\n';
    }
}
