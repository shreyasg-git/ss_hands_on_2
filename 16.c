/*
============================================================================
Name : 16.c
Author : Shreyas Gangurde
Description :16. Write a program to send and receive data from parent to child vice versa. Use two way communication.
Date: 23rd September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd1[2]; // parent -> child
  int fd2[2]; // child -> parent
  pid_t pid;
  char parent_msg[] = "Hello from Parent!";
  char child_msg[] = "Hello from Child!";
  char buffer[100];

  pipe(fd1);
  pipe(fd2);

  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    // child
    close(fd1[1]);
    close(fd2[0]);

    read(fd1[0], buffer, sizeof(buffer));
    printf("Child received: %s\n", buffer);

    write(fd2[1], child_msg, strlen(child_msg) + 1);
    close(fd1[0]);
    close(fd2[1]);
  } else {
    close(fd1[0]);
    close(fd2[1]);

    write(fd1[1], parent_msg, strlen(parent_msg) + 1);

    read(fd2[0], buffer, sizeof(buffer));
    printf("Parent received: %s\n", buffer);

    close(fd1[1]);
    close(fd2[0]);
    wait(NULL);
  }

  return 0;
}
/* OUTPUT

============================================================================
Child received: Hello from Parent!
Parent received: Hello from Child!
============================================================================
*/