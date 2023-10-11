//
// Created by guru on 11.10.23.
//

#ifndef DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H
#define DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H

#include "glue.h"
#include "jsevent.h"
#include <jack/ringbuffer.h>
#include <linux/joystick.h>
#include <string>

class JoystickMidiMediator {
public:
    explicit JoystickMidiMediator(std::string joystickDeviceName);
    void run_main_loop();

private:
    static void event_handler(JoystickEvent event, void *);
    void setupJoystick();
    JsEvents jsEvents;
    jack_ringbuffer_t *jrb = nullptr;
    void sendMidiMessage(const char *msg, size_t size);
};

#endif//DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H
