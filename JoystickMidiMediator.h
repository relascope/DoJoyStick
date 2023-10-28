//
// Created by guru on 11.10.23.
//

#ifndef DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H
#define DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H

#include "DPF/distrho/extra/RingBuffer.hpp"
#include "Settings.h"
#include "joystick-gateway.h"
#include <linux/joystick.h>
#include <string>
#include <thread>

namespace DoJoyStick {

    class JoystickMidiMediator {
    public:
        explicit JoystickMidiMediator(const Settings &settings, HeapRingBuffer *buffer);
        void run_main_loop();
        virtual ~JoystickMidiMediator();

    private:
        static void event_handler(JoystickEvent event, void *);
        void setupJoystick();
        JoystickGateway joystickGateway;
        std::thread joystickThread;

        HeapRingBuffer *buffer;
        void sendMidiMessage(const char *msg, size_t size);
        static void printMidiMessage(const char *msg, size_t size, bool hex = true);
    };
}// namespace DoJoyStick
#endif//DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H
