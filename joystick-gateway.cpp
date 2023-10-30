#include "joystick-gateway.h"

#include <fcntl.h>
#include <iostream>
#include <unistd.h>

#include <cstring>
#include <linux/joystick.h>

namespace DoJoyStick {

    JoystickGateway::JoystickGateway(const std::string joyStickDeviceName) : deviceName(joyStickDeviceName.c_str()) {
        open_joystick();
    }

    void JoystickGateway::setEventHandler(clickHandler handler, void *data) {
        _handler = handler;
        _handlerData = data;
    }

    bool JoystickGateway::open_joystick() {
        char name[128] = "Undefined";
        int buttons;

        if ((joy_fd = open(deviceName, O_RDONLY)) < 0) {
            fprintf(stderr, "Unable to open device ");
            perror(deviceName);
            return false;
        }

        ioctl(joy_fd, JSIOCGBUTTONS, &buttons);
        ioctl(joy_fd, JSIOCGNAME(128), name);

        //        printf("Joystick %s with %i buttons\n", name, buttons);
        return true;
    }

    void JoystickGateway::js_event_loop() {
        struct js_event jsEvent {};
        memset(&jsEvent, 0, sizeof(js_event));

        //        std::cout << "Starting main Joystick query loop. Ctrl-C to exit.\n"
        //                  << "\n";

        long lastTime = 0;
        bool lastDown = false;
        long lastDownTime = 0;
        bool isDouble = false;

        while (shouldRun) {
            if (read(joy_fd, &jsEvent, sizeof(struct js_event)) != sizeof(struct js_event)) {
                perror("Error reading ");
                exit(-1);
            }

            JoystickEvent::CLICK_TYPE curPressType = JoystickEvent::CLICK_TYPE::DOWN;

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

                    curPressType = static_cast<JoystickEvent::CLICK_TYPE>(2 * isHold + 1 * isDouble);

                    isDouble = false;

                    lastDownTime = curTime;
                }

                lastTime = curTime;
                lastDown = curDown;
            }

            if (_handler) {
                (*_handler)({jsEvent, curPressType}, _handlerData);
            }
        }
    }

    int JoystickGateway::close_joystick() {
        if (joy_fd == -1)
            return -1;
        int res;
        errno = 0;
        if ((res = close(joy_fd)) == -1) {
            perror("close joystick");
            exit(1);
        }
        return res;
    }


    JoystickGateway::~JoystickGateway() {
        close_joystick();
    }
}// namespace DoJoyStick