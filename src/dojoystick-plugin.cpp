#pragma clang diagnostic push
#pragma ide diagnostic ignored "clion-misra-cpp2008-10-3-2"
//
// Created by humer on 22/10/2023.
//


#include "dojoystick-plugin.h"
#include "DistrhoPlugin.hpp"
#include "JoystickMidiMediator.h"
#include "Settings.h"
#include <thread>

START_NAMESPACE_DISTRHO


Plugin *createPlugin() { return new DoJoystickPlugin(); }

END_NAMESPACE_DISTRHO
#pragma clang diagnostic pop