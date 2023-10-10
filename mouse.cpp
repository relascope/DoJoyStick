//#include <stdlib.h>
//#include <stdio.h>
//#include <fcntl.h>
//#include <unistd.h>
//#include <linux/input.h>
//
//#include "jsevent.h"
//
//int holdTime = 700;
//int dblTime = 250;
//
//const char *deviceName = "/dev/input/mice";
//
//clickHandler handler = 0;
//
//void setEventHandler(clickHandler _handler) {
//    handler = _handler;
//}
//
//const char *CLICK_TYPE_NAMES[] = {"SINGLE", "DOUBLE", "HOLD", "DOUBLE_HOLD",
//                                  "UNDEF"};
//void printType(CLICK_TYPE t) { printf("%s\n", CLICK_TYPE_NAMES[t]); }
//
//int fd;
//
//int open_joystick() {
//  char name[128] = "Undefined";
//  int buttons;
//
//  if ((fd = open(deviceName, O_RDONLY)) < 0) {
//    fprintf(stderr, "Unable to open device ");
//    perror(deviceName);
//    exit(-1);
//  }
//}
//
//void modiag(struct input_event ie) {
//  //printf("time: %i\n", ie.time);
//  printf("type: %d\n", ie.type);
//  printf("value: %d\n", ie.value);
//  printf("code: %d\n", ie.code);
//}
//
///** TODO Button Numbers!
// * gets events from JoyStick like the Ditto Looper
// * */
//void js_event_loop() {
//  struct input_event ie;
//
//  printf("In loop... Ctrl-C to exit.\n");
//
//  CLICK_TYPE lastType = UNDEF;
//
//  long lastTime = 0;
//  bool lastDown = false;
//
//  long lastDownTime = 0;
//
//  bool isDouble = false;
//
//
//  bool bMiddle, bRight, bLeft;
//  char button;
//
//  while (read(fd, &ie, sizeof(struct input_event))) {
//    unsigned char *ptr = (unsigned char *)&ie;
//    int i;
//    //
//    button = ptr[0];
//    bLeft = button & 0x1;
//    bMiddle = (button & 0x4) > 0;
//    bRight = (button & 0x2) > 0;
//
//    if (bLeft) printf("LEFT\n");
//    if (bMiddle) printf("MIDDLE\n");
//    if (bRight) printf("RIGHT\n");
//
//  }
//
//// TODOJOY up/down
//
///* from joystick
//  while (1) {
//    int readcount = read(fd, &ie, sizeof(struct input_event));
//    if (readcount == -1) {
//      perror("Error reading ");
//      exit(-1);
//    }
//
//    printf("Bytes read: %d\n", readcount);
//
//  modiag(ie);
//
////    jsdiag(js);
//
//    if (js.type == JS_EVENT_BUTTON) {
//      long curTime = js.time;
//      bool curDown = js.value == 1;
//      bool isHold = false;
//
//      if (!lastDown && curDown) {
//        if ((curTime - lastDownTime) < dblTime) {
//          isDouble = true;
//        }
//      }
//
//      if (lastDown && !curDown) {
//        if ((curTime - lastTime) > holdTime) {
//          isHold = true;
//        }
//
//        CLICK_TYPE curType = (CLICK_TYPE)(2 * isHold + 1 * isDouble);
//
//        isDouble = false;
//
//#ifndef NDEBUG
//        printType(curType);
//#endif
//
//        if (handler) {
//            (*handler)(curType);
//        }
//
//        lastDownTime = curTime;
//      }
//
//      lastTime = curTime;
//      lastDown = curDown;
//    }
//  }
//  */
//}
//
//void startJoystickEvents() {
//    open_joystick();
//    js_event_loop();
//}
