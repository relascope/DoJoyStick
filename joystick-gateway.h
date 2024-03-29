#ifndef JSEVENT_H
#define JSEVENT_H

#include "JoystickEvent.h"
#include <atomic>
#include <string>

namespace DoJoyStick {

    /**
 * @brief The JoystickGateway class
 * Reads Joystick events and propagates through EventHandler
 */
    class JoystickGateway {
    public:
        explicit JoystickGateway(std::string joyStickDeviceName = "/dev/input/js0");
        virtual ~JoystickGateway();

        typedef void (*clickHandler)(JoystickEvent, void *data);

        void js_event_loop();

        void setEventHandler(clickHandler handler, void *data = 0);

        static void jsdiag(js_event js);

        void stop() { shouldRun = false; }

    private:
        // TODO allow to set parameters
        int holdTime = 700;
        int dblTime = 250;
        const char *deviceName;
        clickHandler _handler = 0;
        void *_handlerData = 0;
        int joy_fd = -1;
        std::atomic<bool> shouldRun = true;

        bool open_joystick();
        int close_joystick();
    };
}// namespace DoJoyStick
#endif
