/*
============================================================================
Name : 17c.c
Author : Shreyas Gangurde
Description : 17. Write a program to execute ls -l | wc.
                c. use fcntl
Date: 23rd September 2025
============================================================================
*/
#include <fcntl.h>
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

    int new_fd = fcntl(fd[1], F_DUPFD, STDOUT_FILENO);

    if (new_fd != STDOUT_FILENO) {
      close(STDOUT_FILENO);
      dup2(new_fd, STDOUT_FILENO); // just to ensure it's stdout
      close(new_fd);
    }

    close(fd[1]);
    execlp("ls", "ls", "-l", NULL);
    perror("execlp ls");
    exit(1);
  } else {
    close(fd[1]);

    int new_fd = fcntl(fd[0], F_DUPFD, STDIN_FILENO);

    if (new_fd != STDIN_FILENO) {
      close(STDIN_FILENO);
      dup2(new_fd, STDIN_FILENO);
      close(new_fd);
    }

    close(fd[0]);
    execlp("wc", "wc", NULL);
    perror("execlp wc");
    exit(1);
  }

  return 0;
}

/* OUTPUT
============================================================================
     43     380    2414
============================================================================
*/