//
// Created by guru on 11.10.23.
//

#include "JoystickMidiMediator.h"
#include "dojoysticklooper.hpp"
#include "jsevent.h"
#include <iostream>
#include <linux/joystick.h>

JoystickMidiMediator::JoystickMidiMediator(const std::string joystickDeviceName) : jsEvents(joystickDeviceName) {
    jsEvents.setEventHandler(&event_handler, &jsEvents);
}

void JoystickMidiMediator::event_handler(struct js_event event, JsEvents::CLICK_TYPE t, void *) {
    std::cout << "===============EVENT===========" << std::endl;
    JsEvents::jsdiag(event);
    JsEvents::printType(t);
}

void JoystickMidiMediator::run_main_loop() {
    jsEvents.js_event_loop();
}
