#ifndef JSEVENT_H
#define JSEVENT_H

struct js_event;

/**
 * @brief The JsEvents class
 * Reads Joystick events and propagates through EventHandler
 */
class JsEvents {
public:
	typedef enum { SINGLE = 0, DOUBLE, HOLD, DOUBLE_HOLD, UNDEF } CLICK_TYPE;

	typedef void (*clickHandler)(struct js_event event, CLICK_TYPE t, void * data);

	void startJoystickEvents();

	void setEventHandler(clickHandler handler, void *data = 0);

	static void printType(CLICK_TYPE t);

private:

	// TODO allow to set parameters
	int holdTime = 700;
	int dblTime = 250;
	const char *deviceName = "/dev/input/js0";
	clickHandler _handler = 0;
	void * _handlerData = 0;
	int joy_fd;

	void open_joystick();
	void jsdiag(js_event js);
	void js_event_loop();
};

#endif
