/*
============================================================================
Name : 19d.c
Author : Shreyas Gangurde
Description : 19. Create a FIFO file by
                d. mknod system call
Date: 23rd September 2025
============================================================================
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  const char *fifo_name = "myfifo";

  mknod(fifo_name, S_IFIFO | 0666, 0);

  printf("FIFO '%s' created successfully.\n", fifo_name);

  return 0;
}
/* OUTPUT
============================================================================
FIFO 'myfifo' created successfully.
============================================================================
*/