//
// Created by guru on 11.10.23.
//

#ifndef DOJOYSTICK_ACTIONMAPPER_H
#define DOJOYSTICK_ACTIONMAPPER_H

////////////////////////////////////////////////////////////////////////
// Button #4,5,6,7 are A,B,C,D on Joystick Microsoft Microsoft SideWinder Precision Pro
// for the time just hardcode to be a good left foot pedal for x42 Black Pearl drumkit

#include "JoystickEvent.h"
class ActionMapper{
public:
    void performActionsForEvent(JoystickEvent event);
};


#endif//DOJOYSTICK_ACTIONMAPPER_H
