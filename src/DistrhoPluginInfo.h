//
// Created by humer on 22/10/2023.
//

#ifndef DISTRHO_PLUGIN_INFO_H_INCLUDED
#define DISTRHO_PLUGIN_INFO_H_INCLUDED

#define DISTRHO_PLUGIN_NAME  "DoJoystick"
#define DISTRHO_PLUGIN_URI   "https://dojoy.at.com/REIS0/DPFTutorial"
#define DISTRHO_PLUGIN_CLAP_ID "https://dojoy.com/REIS0/DPFTutorial"

#define DISTRHO_PLUGIN_WANT_MIDI_OUTPUT 2
#define DISTRHO_PLUGIN_NUM_INPUTS   0
#define DISTRHO_PLUGIN_NUM_OUTPUTS  0
#define DISTRHO_PLUGIN_IS_RT_SAFE   1

//#define DISTRHO_PLUGIN_HAS_UI       1

enum Parameters {
    kGain,
    kParameterCount
};

#endif