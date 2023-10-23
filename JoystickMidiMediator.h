//
// Created by guru on 11.10.23.
//

#ifndef DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H
#define DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H

#include "DPF/distrho/extra/RingBuffer.hpp"
#include "joystick-gateway.h"
#include <linux/joystick.h>
#include <string>

class JoystickMidiMediator {
public:
    explicit JoystickMidiMediator(const std::string &joystickDeviceName, HeapRingBuffer *buffer);
    void run_main_loop();

private:
    static void event_handler(JoystickEvent event, void *);
    void setupJoystick();
    JoystickGateway joystickGateway;
    HeapRingBuffer *buffer;
    void sendMidiMessage(const char *msg, size_t size);
    static void printMidiMessage(const char *msg, size_t size, bool hex = true);
};

#endif//DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H
