/*
============================================================================
Name : 19e.c
Author : Shreyas Gangurde
Description : 19. Create a FIFO file by
                e. mkfifo library function
Date: 23rd September 2025
============================================================================
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  const char *fifo_name = "myfifo";

  mkfifo(fifo_name, 0666);

  printf("FIFO '%s' created successfully.\n", fifo_name);

  return 0;
}
/* OUTPUT
============================================================================
FIFO 'myfifo' created successfully.
============================================================================
*/