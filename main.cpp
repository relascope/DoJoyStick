// TODO Different Buttons

#include "dojoysticklooper.hpp"


#include "JoystickMidiMediator.h"
//#include "joystick-gateway.h"


int main(int argc, char *argv[]) {
//	DoJoyStickLooper looper;

//	looper.start();

    JoystickMidiMediator joystick_midi("/dev/input/js0");
    joystick_midi.run_main_loop();

    return 0;
}
