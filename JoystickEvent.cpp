//
// Created by guru on 11.10.23.
//
#include "JoystickEvent.h"
#include <iostream>

std::string JoystickEvent::clickTypeToString(CLICK_TYPE clickType) const {
    static const char *CLICK_TYPE_NAMES[] = {"SINGLE", "DOUBLE", "HOLD", "DOUBLE_HOLD",
                                             "DOWN"};

    return CLICK_TYPE_NAMES[clickType];
}

void JoystickEvent::print() const {
    std::cout << "================================================================" << ' \n';
    std::cout << clickTypeToString(this->clickType) << '\n';
    print_js_event(this->nativeEvent);
    std::cout << "----------------------------------------------------------------" << '\n';
}

void JoystickEvent::print_js_event(struct js_event js) {
    std::cout << "time: " << js.time << '\n';
    std::cout << "value (up/down): " << js.value << '\n';
    std::cout << "type (button/axis): " << (int) js.type << '\n';
    std::cout << "number: " << (int)js.number << '\n';
}
