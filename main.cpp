// TODO Undo/Redo
// TODO Different Buttons

// TODO for fun test with mousebuttons or keyboard...

// TODO NDEBUG ?? means NOT no debug ??
// http://stuffusedinworking.blogspot.co.at/2011/01/useage-of-ndebug-macros.html


#define DEBUG_OUTPUT

#include "jsevent.h"

//#include "mouseevent.c"

#include <stdio.h>
#include <stdlib.h>

#include <functional>

// Record Tap footswitch once.
// Switch to playback Tap footswitch again.
// Undo/Redo last recording Press and hold footswitch.
// Stop Double-tap footswitch.
// Stop and delete the loop Double-tap and hold footswitch.
// Resume playback Tap footswitch again.
// Delete the loop Press and hold footswitch
// (when Ditto Looper is disengaged).
//
//
//


// SOOPERLOOPER OSC commands (some of them)
// http://essej.net/sooperlooper/doc_osc.html


//typedef enum {
//  RECORD = 0,
//  PLAYBACK,
//  UNDO_REDO,
//  STOP,
//  STOP_DELETE,
//  RESUME,
//  DELETE
//} COMMAND;

//const char *COMMAND_NAMES[] = {"RECORD",      "PLAYBACK", "UNDO_REDO", "STOP",
//                               "STOP_DELETE", "RESUME",   "DELETE"};

//void printCommand(COMMAND c) { printf("%s\n", COMMAND_NAMES[c]); }


//const char *OSC_COMMANDS[] = {
//    "oscsend osc.udp://localhost:9951 /sl/-1/hit s record",


//};


typedef enum {
    JUST_STARTED = 0,
    STOPPED,
    RECORDING,
    OVERDUBBING,
    PLAYBACK
} LOOPER_STATUS;

const char *LOOPER_STATUS_NAMES[] = {"JUST_STARTED", "STOPPED", "RECORDING", "OVERDUBBING", "PLAYBACK"};

void printLooperStatus(LOOPER_STATUS ls) { printf("%s\n", LOOPER_STATUS_NAMES[ls]); }


LOOPER_STATUS loopStatus = JUST_STARTED;


void dittoHandler(JsEvents::CLICK_TYPE clickType) {

#ifndef NDEBUG
    printf("_____EVENT_____\n");
    printLooperStatus(loopStatus);
#endif


	if (clickType == JsEvents::DOUBLE) {
        system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_on");
        loopStatus = STOPPED;
        goto dittoHandlerEnd;
    }

	if (clickType == JsEvents::DOUBLE_HOLD) {
        system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_on");
        loopStatus = JUST_STARTED;
    }


    switch (loopStatus) {
    case JUST_STARTED:
        switch (clickType) {
			case JsEvents::SINGLE:
                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s record");
                loopStatus = RECORDING;
                break;
			case JsEvents::HOLD:
                break;
			case JsEvents::DOUBLE_HOLD:
                break;
			case JsEvents::DOUBLE:
            // NOTHING
                break;
            default:
                fprintf(stderr, "CLICKTYPE NOT DEFINED");
				JsEvents::printType(clickType);
                break;
        }
        break;
    case RECORDING:
        switch (clickType) {
			case JsEvents::SINGLE:
                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s record");
                loopStatus = PLAYBACK;
                break;
			case JsEvents::HOLD:
                break;
			case JsEvents::DOUBLE_HOLD:
                break;
			case JsEvents::DOUBLE:
//                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s record"); // done by SINGLE
//                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_on");
//                loopStatus = STOPPED;
                break;
            default:
                fprintf(stderr, "CLICKTYPE NOT DEFINED");
				JsEvents::printType(clickType);
                break;
        }
        break;

    case OVERDUBBING:
        switch (clickType) {
			case JsEvents::SINGLE:
                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s overdub");
                loopStatus = PLAYBACK;
                break;
			case JsEvents::HOLD:
                break;
			case JsEvents::DOUBLE_HOLD:
                break;
			case JsEvents::DOUBLE:
                break;
            default:
                fprintf(stderr, "CLICKTYPE NOT DEFINED");
				JsEvents::printType(clickType);
                break;
        }
        break;

    case STOPPED:
        switch (clickType) {
			case JsEvents::SINGLE:
                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_off");
                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s trigger");
                // TODO what does ditto do? record/playback
                loopStatus = PLAYBACK;
                break;
			case JsEvents::HOLD:
                break;
			case JsEvents::DOUBLE_HOLD:
                break;
			case JsEvents::DOUBLE:
                break;
            default:
                fprintf(stderr, "CLICKTYPE NOT DEFINED");
				JsEvents::printType(clickType);
                break;
        }
        break;
    case PLAYBACK:
        switch (clickType) {
			case JsEvents::SINGLE:
//                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s overdub");
//                loopStatus = OVERDUBBING;
                break;
			case JsEvents::HOLD:
                break;
			case JsEvents::DOUBLE_HOLD:
                break;
			case JsEvents::DOUBLE:
                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_on");
                loopStatus = STOPPED;
                break;
            default:
                fprintf(stderr, "CLICKTYPE NOT DEFINED");
				JsEvents::printType(clickType);
                break;
        }
        break;
    default:
        fprintf(stderr, "LOOPER_STATUS NOT DEFINED");
        printLooperStatus(loopStatus);
    }

    dittoHandlerEnd:
#ifndef NDEBUG
    printLooperStatus(loopStatus);
#endif
}

#include "looper.h"

using namespace smlooper;


static char const* const state_names[] = {"Stopped", "Recording", "Playback"};


class LooperBackend {
public:
	virtual void record() = 0;
	virtual void stop() = 0;
	virtual void playback() = 0;
};

class SLBackend : public LooperBackend {


	// LooperBackend interface
public:
	void record();
	void stop();
	void playback();
};

class DoJoyStickLooper {
public:

	DoJoyStickLooper() {
		init();
	}

	static void looperEventHandler(JsEvents::CLICK_TYPE clickType, void * data) {
		// TODO checking for null and conversion error...
		DoJoyStickLooper *_this = static_cast<DoJoyStickLooper*> (data);

		switch (clickType) {
			case JsEvents::SINGLE:
				_this->_looper.process_event(smlooper::CLICK());
				break;
			case JsEvents::DOUBLE:
				_this->_looper.process_event( smlooper::DBL_CLICK());
				break;
			case JsEvents::HOLD:
				_this->_looper.process_event(smlooper::HOLD());
				break;
			case JsEvents::DOUBLE_HOLD:
				_this->_looper.process_event(smlooper::DBL_HOLD());
				break;
			default:
				throw "Undefinded ClickType";
				break;
		}

		_this->pstate();
	}

	virtual ~DoJoyStickLooper() {
		_looper.stop();
	}

private:
	looper _looper;
	JsEvents _events;

	void init() {
		_looper.start();

		_events.setEventHandler(&DoJoyStickLooper::looperEventHandler, this);
		_events.startJoystickEvents();
	}

	void pstate() const {
		std::cout << " -> " << state_names[_looper.current_state()[0]] << std::endl;
	}
};

int main(int argc, char *argv[]) {
#ifndef NDEBUG
	printf("Clearing loops to add a single one. Compile with -DNDEBUG to avoid debugging behaviour! \n");
	system("oscsend osc.udp://localhost:9951 /loop_del i -1");
	system("oscsend osc.udp://localhost:9951 /loop_add ii 2 0");
#endif

	DoJoyStickLooper looper;

    return 0;
}
