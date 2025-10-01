/*
============================================================================
Name : 23.c
Author : Shreyas Gangurde
Description : 23. Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date: 1st October 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  long max_files = sysconf(_SC_OPEN_MAX);

  printf("Maximum number of files a process can open: %ld\n", max_files);

  int fd[2];

  pipe(fd);

  long pipe_size = fpathconf(fd[0], _PC_PIPE_BUF);

  printf("size of the pipe(circular buffer): %ld\n", pipe_size);

  return 0;
}

/* OUTPUT
============================================================================
Maximum number of files a process can open: 1024
size of the pipe(circular buffer): 4096
============================================================================
*/