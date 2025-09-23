/*
============================================================================
Name : 15.c
Author : Shreyas Gangurde
Description : 15. Write a simple program to send some data from parent to the child process.
Date: 23rd September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  int fd[2]; // read, write
  pid_t pid;
  char msg[] = "Hello from Parent!";
  char buffer[100];

  pipe(fd);

  pid = fork();

  if (pid == 0) {
    close(fd[1]);
    read(fd[0], buffer, sizeof(buffer));
    printf("Child received: %s\n", buffer);
    close(fd[0]);
  } else {
    close(fd[0]);
    write(fd[1], msg, strlen(msg) + 1);
    printf("Parent sent: %s\n", msg);
    close(fd[1]);
  }

  return 0;
}
/* OUTPUT

============================================================================
Parent sent: Hello from Parent!
Child received: Hello from Parent!
============================================================================
*/