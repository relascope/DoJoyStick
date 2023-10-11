#include "jsevent.h"

#include <fcntl.h>
#include <iostream>
#include <unistd.h>

#include <cstring>
#include <linux/joystick.h>

JsEvents::JsEvents(const std::string joyStickDeviceName) : deviceName(joyStickDeviceName.c_str()) {
    open_joystick();
}

void JsEvents::setEventHandler(clickHandler handler, void *data) {
    _handler = handler;
    _handlerData = data;
}

const char *CLICK_TYPE_NAMES[] = {"SINGLE", "DOUBLE", "HOLD", "DOUBLE_HOLD",
                                  "UNDEF"};

void JsEvents::printType(CLICK_TYPE t) {
    std::cout << CLICK_TYPE_NAMES[t] << std::endl;
}

void JsEvents::open_joystick() {
    char name[128] = "Undefined";
    int buttons;

    if ((joy_fd = open(deviceName, O_RDONLY)) < 0) {
        fprintf(stderr, "Unable to open device ");
        perror(deviceName);
        exit(-1);
    }

    ioctl(joy_fd, JSIOCGBUTTONS, &buttons);
    ioctl(joy_fd, JSIOCGNAME(128), name);

    printf("Joystick %s with %i buttons\n", name, buttons);
}

void JsEvents::jsdiag(struct js_event js) {
    printf("time: %i\n", js.time);
    printf("value: %i\n", js.value);
    printf("type: %i\n", js.type);
    printf("number: %i\n", js.number);
}

void JsEvents::js_event_loop() {
    struct js_event jsEvent {};
    memset(&jsEvent, 0, sizeof(js_event));

    std::cout << "Starting main Joystick query loop. Ctrl-C to exit.\n"
              << "\n";

    long lastTime = 0;
    bool lastDown = false;
    long lastDownTime = 0;
    bool isDouble = false;

    while (true) {
        if (read(joy_fd, &jsEvent, sizeof(struct js_event)) != sizeof(struct js_event)) {
            perror("Error reading ");
            exit(-1);
        }

        CLICK_TYPE curPressType = CLICK_TYPE::UNDEF;

        if (jsEvent.type == JS_EVENT_BUTTON) {
            __u32 curTime = jsEvent.time;
            bool curDown = jsEvent.value == 1;
            bool isHold = false;

            if (!lastDown && curDown) {
                if ((curTime - lastDownTime) < dblTime) {
                    isDouble = true;
                }
            }

            if (lastDown && !curDown) {
                if ((curTime - lastTime) > holdTime) {
                    isHold = true;
                }

                curPressType = (CLICK_TYPE) (2 * isHold + 1 * isDouble);

                isDouble = false;

                lastDownTime = curTime;
            }

            lastTime = curTime;
            lastDown = curDown;
        }

        if (_handler) {
            (*_handler)(jsEvent, curPressType, _handlerData);
        }
    }
}
