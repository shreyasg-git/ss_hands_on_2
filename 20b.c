/*
============================================================================
Name : 20b.c
Author : Shreyas Balasaheb Gangurde
Description : 20. Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 10th September 2025
============================================================================
*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int fd;
  char *myfifo = "/tmp/myfifo";

  mkfifo(myfifo, 0666);

  char buf[80];

  while (1) {
    fd = open(myfifo, O_RDONLY);
    read(fd, buf, sizeof(buf));
    printf("[SENDER] :: %s", buf);
    close(fd);

    // return 0;
  }
}

/* TERMINAL ONE - SENDER
============================================================================
Hello
World
How are you
============================================================================


TERMINAL TWO - RECEIVER
============================================================================
[SENDER] :: Hello
[SENDER] :: World
[SENDER] :: How are you
============================================================================

*/