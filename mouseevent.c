//#include <stdio.h>
//#include <stdlib.h>
//#include <fcntl.h>
//#include <linux/input.h>
//#include <unistd.h>
//
//
//#define MOUSEFILE "/dev/input/mouse0\0"
////
//int main() {
//  int fd;
//  struct input_event ie;
//  unsigned char *ptr = (unsigned char *)&ie;
//  //
//  unsigned char button, bLeft, bMiddle, bRight;
//  char x, y;  // the relX , relY datas
//  int absolute_x, absolute_y;
//
//  if ((fd = open(MOUSEFILE, O_RDONLY | O_NONBLOCK)) == -1) {
//    printf("NonBlocking %s open ERROR\n", MOUSEFILE);
//    perror("");
//    exit(EXIT_FAILURE);
//  } else {
//    printf("NonBlocking %s open OK\n", MOUSEFILE);
//  }
//  //
//  printf("--------------------------------------------------------\n");
//  printf("right-click to set absolute x,y coordinates origin (0,0)\n");
//  printf("left+right click to EXIT\n");
//  printf("--------------------------------------------------------\n");
//  //
//  while (1) {
//    if (read(fd, &ie, sizeof(struct input_event)) != -1) {
//	  //CLICK_TYPE
//      button = ptr[0];
//      bLeft = button & 0x1;
//      bMiddle = (button & 0x4) > 0;
//      bRight = (button & 0x2) > 0;
//      x = (char)ptr[1];
//      y = (char)ptr[2];
//      if (bLeft & bRight) {
//        printf("\nright+left ,EXIT\n");
//        break;
//      }
//      // computes absolute x,y coordinates
//      absolute_x += x;
//      absolute_y -= y;
//      // set absolute reference ?
//      if (bRight == 1) {
//        absolute_x = 0;
//        absolute_y = 0;
//        printf("Absolute x,y coords origin recorded\n");
//      }
//      // show it!
//      printf("X%i Y%i\n", absolute_x, absolute_y);
//      fflush(stdout);
//    }
//  }
//  //
//  close(fd);
//  return 0;
//}
