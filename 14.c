/*
============================================================================
Name : 14.c
Author : Shreyas Gangurde
Description : 14. Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 23rd September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  int fd[2];
  char write_msg[] = "Hello through pipe!";
  char read_msg[100];

  pipe(fd);

  printf("Writing to pipe: %s\n", write_msg);
  write(fd[1], write_msg, strlen(write_msg) + 1);

  read(fd[0], read_msg, sizeof(read_msg));
  printf("Read from pipe: %s\n", read_msg);

  close(fd[0]);
  close(fd[1]);

  return 0;
}

/* OUTPUT

============================================================================
Writing to pipe: Hello through pipe!
Read from pipe: Hello through pipe!
============================================================================
*/