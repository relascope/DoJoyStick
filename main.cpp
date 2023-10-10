// TODO Different Buttons

#include "dojoysticklooper.hpp"
#include <linux/joystick.h>

#include "jsevent.h"


void event_handler(struct js_event event, JsEvents::CLICK_TYPE t, void * data) {
    JsEvents::printType(t);
}

int main(int argc, char *argv[]) {
//	DoJoyStickLooper looper;

//	looper.start();

    JsEvents jsEvents;
    jsEvents.setEventHandler(&event_handler, &jsEvents);
    jsEvents.startJoystickEvents();

    return 0;
}
