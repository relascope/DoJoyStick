//
// Created by guru on 11.10.23.
//

#ifndef DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H
#define DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H

#include "jsevent.h"
#include <jack/ringbuffer.h>
#include <linux/joystick.h>
#include <string>

class JoystickMidiMediator {
public:
    explicit JoystickMidiMediator(std::string joystickDeviceName);
    void run_main_loop();

private:
    static void event_handler(struct js_event event, JsEvents::CLICK_TYPE t, void *);
    void setupJoystick();
    JsEvents jsEvents;
    jack_ringbuffer_t *jrb = nullptr;
};

#endif//DOJOYSTICK_JOYSTICKMIDIMEDIATOR_H
