

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

#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <linux/joystick.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <time.h>
#include <math.h>

inline long millis() {
  long ms;
  struct timespec spec;
  clock_gettime(CLOCK_MONOTONIC, &spec);
  ms = round(spec.tv_nsec / 1.0e6);
  return ms;
}

typedef enum {
  RECORD = 0,
  PLAYBACK,
  UNDO_REDO,
  STOP,
  STOP_DELETE,
  RESUME,
  DELETE
} COMMAND;

const char *COMMAND_NAMES[] = {"RECORD",      "PLAYBACK", "UNDO_REDO", "STOP",
                               "STOP_DELETE", "RESUME",   "DELETE"};

void printCommand(COMMAND c) { printf("%s\n", COMMAND_NAMES[c]); }

typedef enum { SINGLE = 0, DOUBLE, HOLD, DOUBLE_HOLD, UNDEF } CLICK_TYPE;

const char *CLICK_TYPE_NAMES[] = {"SINGLE", "DOUBLE", "HOLD", "DOUBLE_HOLD",
                                  "UNDEF"};

void printType(CLICK_TYPE t) { printf("%s\n", CLICK_TYPE_NAMES[t]); }



void ditto_event(CLICK_TYPE type) {
    switch (type) {
	case HOLD:
	    system("/home/dojoy/dev/linux/togglejack.sh");
	    break;
	case SINGLE:
	    break;
	case DOUBLE_HOLD:
	    break;
	case DOUBLE:
	    break;
    }
}








int joy_fd;
int open_joystick() {
  char name[128] = "Undefined";
  int buttons;

  if ((joy_fd = open("/dev/input/js0", O_RDONLY)) < 0) {
    fprintf(stderr, "Unable to open device ");
    perror("/dev/input/js0");
    exit(-1);
  }

  ioctl(joy_fd, JSIOCGBUTTONS, &buttons);
  ioctl(joy_fd, JSIOCGNAME(128), name);

  printf("Joystick %s with %i buttons\n", name, buttons);
}

void jsdiag(struct js_event js) {
  printf("time: %i\n", js.time);
  printf("value: %i\n", js.value);
  printf("type: %i\n", js.type);
  printf("number: %i\n", js.number);
}

int holdTime = 700;
int dblTime = 250;

/** TODO Button Numbers!
 * gets events from JoyStick like the Ditto Looper
 * */
void ditto_loop() {
  struct js_event js;

  printf("In loop... Ctrl-C to exit.\n");

  CLICK_TYPE lastType = UNDEF;

  long lastTime = 0;
  bool lastDown = false;

  long lastDownTime = 0;

  bool isDouble = false;

  while (1) {
    if (read(joy_fd, &js, sizeof(struct js_event)) != sizeof(struct js_event)) {
      perror("Error reading ");
      exit(-1);
    }

//    jsdiag(js);

    if (js.type == JS_EVENT_BUTTON) {
      long curTime = js.time;
      bool curDown = js.value == 1;
      bool isHold = false;

      if (!lastDown && curDown) {
        if ((curTime - lastDownTime) < dblTime) {
          isDouble = true;
        }
      }

      if (lastDown && !curDown) {
        if ((curTime - lastTime) > holdTime) {
          isHold = true;
        }

        CLICK_TYPE curType = (CLICK_TYPE)(2 * isHold + 1 * isDouble);

        isDouble = false;

	// TODO Add handler
        printType(curType);
	ditto_event(curType);
        lastDownTime = curTime;
      }

      lastTime = curTime;
      lastDown = curDown;
    }
  }
}

int main(int argc, char *argv[]) {
  open_joystick();

  ditto_loop();
  return 0;
}
