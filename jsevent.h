#ifndef JSEVENT_H
#define JSEVENT_H

struct js_event;

class JsEvents {
public:
	typedef enum { SINGLE = 0, DOUBLE, HOLD, DOUBLE_HOLD, UNDEF } CLICK_TYPE;

	typedef void (*clickHandler)(CLICK_TYPE t);

	void startJoystickEvents();

	void setEventHandler(clickHandler handler);

	static void printType(CLICK_TYPE t);

private:

	// TODO allow to set parameters
	int holdTime = 700;
	int dblTime = 250;
	const char *deviceName = "/dev/input/js0";
	clickHandler handler = 0;

	int open_joystick();
	void jsdiag(js_event js);
	void js_event_loop();
};

#endif
