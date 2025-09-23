/*
============================================================================
Name : 18.c
Author : Shreyas Gangurde
Description : 18. Write a program to find out total number of directories on the pwd. execute ls -l | grep ^d | wc ? Use only dup2.
Date: 23rd September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pipe1[2]; // ls -> grep
  int pipe2[2]; // grep -> wc

  pipe(pipe1);
  pipe(pipe2);

  pid_t pid1 = fork();

  if (pid1 == 0) {
    close(pipe1[0]);
    dup2(pipe1[1], STDOUT_FILENO);
    close(pipe1[1]);

    close(pipe2[0]);
    close(pipe2[1]);

    execlp("ls", "ls", "-l", NULL);
    perror("execlp ls");
    exit(1);
  }

  pid_t pid2 = fork();

  if (pid2 == 0) {
    // Second child: grep ^d
    close(pipe1[1]);
    dup2(pipe1[0], STDIN_FILENO);
    close(pipe1[0]);

    close(pipe2[0]);
    dup2(pipe2[1], STDOUT_FILENO);
    close(pipe2[1]);

    execlp("grep", "grep", "^d", NULL);
    perror("execlp grep");
    exit(1);
  }

  // Parent process: wc
  close(pipe1[0]);
  close(pipe1[1]);
  close(pipe2[1]);
  dup2(pipe2[0], STDIN_FILENO);
  close(pipe2[0]);

  execlp("wc", "wc", NULL);
  perror("execlp wc");
  exit(1);

  return 0;
}
/* OUTPUT
============================================================================
      1       9      58
============================================================================
*/