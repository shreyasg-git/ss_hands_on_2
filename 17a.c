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
    pid_t pid1, pid2;

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid1 == 0) {
        close(fd[0]);
        close(STDOUT_FILENO);
        dup(fd[1]);
        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls failed");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid2 == 0) {
        close(fd[1]);
        close(STDIN_FILENO);
        dup(fd[0]);
        close(fd[0]);

        execlp("wc", "wc", NULL);
        perror("execlp wc failed");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}

/* OUTPUT
============================================================================
     41     362    2297
============================================================================
*/