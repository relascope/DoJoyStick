//
// Created by guru on 28.10.23.
//

#ifndef DOJOYSTICK_SETTINGS_H_
#define DOJOYSTICK_SETTINGS_H_

#include <cstdint>
#include <string>

namespace DoJoyStick {

    struct Settings {
        uint8_t velocity;
        std::string joyStickDeviceName;
    };

}// namespace DoJoyStick

#endif//DOJOYSTICK__SETTINGS_H_
