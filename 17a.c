/*
============================================================================
Name : 17a.c
Author : Shreyas Gangurde
Description : 17. Write a program to execute ls -l | wc.
                a. use dup
Date: 23rd September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd[2];
  pid_t pid;

  pipe(fd);

  pid = fork();

  if (pid == 0) {
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);

    execlp("ls", "ls", "-l", NULL);
    perror("execlp ls");
    exit(1);
  } else {
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);

    execlp("wc", "wc", NULL);
    perror("execlp wc");
    exit(1);
  }

  return 0;
}

/* OUTPUT
============================================================================
     41     362    2297
============================================================================
*/