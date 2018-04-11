#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>

#define MOUSEFILE "/dev/input/mice"
//
int main() {
  int fd;
  struct input_event ie;
  //
  unsigned char button, bLeft, bMiddle, bRight;
  char x, y;
  int absolute_x, absolute_y;

  if ((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
    printf("Device open ERROR\n");
    exit(EXIT_FAILURE);
  } else {
    printf("Device open OK\n");
  }
  //
  printf("right-click to set absolute x,y coordinates origin (0,0)\n");
  while (read(fd, &ie, sizeof(struct input_event))) {
	  
	  
	  printf("type: %u\tcode: %u\tvalue: %d \n", ie.type, ie.code, ie.value);
	  
	  printf("EV_KEY = %u\nBTN_LEFT = %u \n", EV_KEY, BTN_LEFT);
	  
	  if (ie.type == EV_KEY) {
		  printf("KEY\n");
	  }
	  
	  if (ie.code == BTN_LEFT) {
		  printf("BTN_LEFT\n"); 
	  }
	  
    unsigned char *ptr = (unsigned char *)&ie;
    int i;
    //
    button = ptr[0];
    bLeft = button & 0x1;
    bMiddle = (button & 0x4) > 0;
    bRight = (button & 0x2) > 0;
    x = (char)ptr[1];
    y = (char)ptr[2];
    printf("bLEFT:%d, bMIDDLE: %d, bRIGHT: %d, rx: %d  ry=%d\n", bLeft, bMiddle,
           bRight, x, y);
    //
    absolute_x += x;
    absolute_y -= y;
    if (bRight == 1) {
      absolute_x = 0;
      absolute_y = 0;
      printf("Absolute x,y coords origin recorded\n");
    }
    //
    printf("Absolute coords from TOP_LEFT= %i %i\n", absolute_x, absolute_y);
    //
    // comment to disable the display of raw event structure datas
    //
    for (i = 0; i < sizeof(ie); i++) {
      printf("%02X ", *ptr++);
    }
    printf("\n");
  }

  return 0;
}
