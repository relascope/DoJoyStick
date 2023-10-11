#ifndef JSEVENT_H
#define JSEVENT_H

#include <string>
struct js_event;

/**
 * @brief The JsEvents class
 * Reads Joystick events and propagates through EventHandler
 */
class JsEvents {
public:
    JsEvents(std::string joyStickDeviceName = "/dev/input/js0");

	typedef enum { SINGLE = 0, DOUBLE, HOLD, DOUBLE_HOLD, UNDEF } CLICK_TYPE;

	typedef void (*clickHandler)(struct js_event event, CLICK_TYPE t, void * data);

	void js_event_loop();

	void setEventHandler(clickHandler handler, void *data = 0);

	static void printType(CLICK_TYPE t);

    static void jsdiag(js_event js);
private:

	// TODO allow to set parameters
	int holdTime = 700;
	int dblTime = 250;
	const char *deviceName;
	clickHandler _handler = 0;
	void * _handlerData = 0;
	int joy_fd;

	void open_joystick();
};

#endif
