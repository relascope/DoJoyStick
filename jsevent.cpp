#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
//#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/joystick.h>

#include "jsevent.h"




int holdTime = 700;
int dblTime = 250;

const char *deviceName = "/dev/input/js0";

clickHandler handler = 0;

void setEventHandler(clickHandler _handler) {
    handler = _handler;
}

const char *CLICK_TYPE_NAMES[] = {"SINGLE", "DOUBLE", "HOLD", "DOUBLE_HOLD",
                                  "UNDEF"};
void printType(CLICK_TYPE t) { printf("%s\n", CLICK_TYPE_NAMES[t]); }

int joy_fd;

int open_joystick() {
  char name[128] = "Undefined";
  int buttons;

  if ((joy_fd = open(deviceName, O_RDONLY)) < 0) {
    fprintf(stderr, "Unable to open device ");
    perror(deviceName);
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

/** TODO Button Numbers!
 * gets events from JoyStick like the Ditto Looper
 * */
void js_event_loop() {
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

#ifndef NDEBUG
        printType(curType);
#endif

        if (handler) {
            (*handler)(curType);
        }

        lastDownTime = curTime;
      }

      lastTime = curTime;
      lastDown = curDown;
    }
  }
}

void startJoystickEvents() {
    open_joystick();
    js_event_loop();
}
