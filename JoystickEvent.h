//
// Created by guru on 11.10.23.
//

#ifndef DOJOYSTICK_JOYSTICKEVENT_H
#define DOJOYSTICK_JOYSTICKEVENT_H

#include <linux/joystick.h>
#include <string>

class JoystickEvent {
public:
    typedef enum { SINGLE = 0,
                   DOUBLE,
                   HOLD,
                   DOUBLE_HOLD,
                   DOWN } CLICK_TYPE;

public:
    JoystickEvent(js_event deviceEvent, CLICK_TYPE t) : nativeEvent(deviceEvent), clickType(t) {}

    int getButtonNumber() const {
        return nativeEvent.number;
    }

    bool isButtonDown() const { return nativeEvent.value == 1; }
    bool isButtonUp() const { return nativeEvent.value == 0; }

    void print() const;

    void print(CLICK_TYPE type) const;
    static void print_js_event(struct js_event js);
    std::string clickTypeToString(CLICK_TYPE clickType) const;

    js_event getNativeEvent() const { return nativeEvent; }
    CLICK_TYPE getClickType() const { return clickType; }

private:
    js_event nativeEvent;
    CLICK_TYPE clickType;
};

#endif//DOJOYSTICK_JOYSTICKEVENT_H
