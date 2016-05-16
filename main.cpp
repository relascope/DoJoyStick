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


void dittoHandler(CLICK_TYPE clickType) {

#ifndef NDEBUG
    printf("_____EVENT_____\n");
    printLooperStatus(loopStatus);
#endif


    if (clickType == DOUBLE) {
        system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_on");
        loopStatus = STOPPED;
        goto dittoHandlerEnd;
    }

    if (clickType == DOUBLE_HOLD) {
        system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_on");
        loopStatus = JUST_STARTED;
    }


    switch (loopStatus) {
    case JUST_STARTED:
        switch (clickType) {
            case SINGLE:
                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s record");
                loopStatus = RECORDING;
                break;
            case HOLD:
                break;
            case DOUBLE_HOLD:
                break;
            case DOUBLE:
            // NOTHING
                break;
            default:
                fprintf(stderr, "CLICKTYPE NOT DEFINED");
                printType(clickType);
                break;
        }
        break;
    case RECORDING:
        switch (clickType) {
            case SINGLE:
                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s record");
                loopStatus = PLAYBACK;
                break;
            case HOLD:
                break;
            case DOUBLE_HOLD:
                break;
            case DOUBLE:
//                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s record"); // done by SINGLE
//                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_on");
//                loopStatus = STOPPED;
                break;
            default:
                fprintf(stderr, "CLICKTYPE NOT DEFINED");
                printType(clickType);
                break;
        }
        break;

    case OVERDUBBING:
        switch (clickType) {
            case SINGLE:
                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s overdub");
                loopStatus = PLAYBACK;
                break;
            case HOLD:
                break;
            case DOUBLE_HOLD:
                break;
            case DOUBLE:
                break;
            default:
                fprintf(stderr, "CLICKTYPE NOT DEFINED");
                printType(clickType);
                break;
        }
        break;

    case STOPPED:
        switch (clickType) {
            case SINGLE:
                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_off");
                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s trigger");
                // TODO what does ditto do? record/playback
                loopStatus = PLAYBACK;
                break;
            case HOLD:
                break;
            case DOUBLE_HOLD:
                break;
            case DOUBLE:
                break;
            default:
                fprintf(stderr, "CLICKTYPE NOT DEFINED");
                printType(clickType);
                break;
        }
        break;
    case PLAYBACK:
        switch (clickType) {
            case SINGLE:
//                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s overdub");
//                loopStatus = OVERDUBBING;
                break;
            case HOLD:
                break;
            case DOUBLE_HOLD:
                break;
            case DOUBLE:
                system("oscsend osc.udp://localhost:9951 /sl/-1/hit s mute_on");
                loopStatus = STOPPED;
                break;
            default:
                fprintf(stderr, "CLICKTYPE NOT DEFINED");
                printType(clickType);
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

int main(int argc, char *argv[]) {

#ifndef NDEBUG
    printf("Clearing loop to add a single one. Compile with -DNDEBUG to avoid debugging behaviour! \n");
    system("oscsend osc.udp://localhost:9951 /loop_del i -1");
    system("oscsend osc.udp://localhost:9951 /loop_add ii 2 0");
#endif

    setEventHandler(&dittoHandler);

    startJoystickEvents();
    return 0;
}
