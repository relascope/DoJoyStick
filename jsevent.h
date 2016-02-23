#ifndef JSEVENT_H
#define JSEVENT_H

typedef enum { SINGLE = 0, DOUBLE, HOLD, DOUBLE_HOLD, UNDEF } CLICK_TYPE;

typedef void (*clickHandler)(CLICK_TYPE t);

void startJoystickEvents();

void setEventHandler(clickHandler handler);

void printType(CLICK_TYPE t);

#endif
