/*
============================================================================
Name : 13a.c
Author : Shreyas Gangurde
Description : 13. Write two programs: first program is waiting to catch SIGSTOP
signal, the second program will send the signal (using kill system call). Find
out whether the first program is able to catch the signal or not. Date: 23rd
September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo) { printf("Caught signal %d\n", signo); }

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // this will silently fail
    sigaction(SIGSTOP, &sa, NULL);

    printf("Process PID = %d\n", getpid());
    printf("Waiting for signals (try sending SIGSTOP)...\n");

    while (1) {
        pause();  // wait for signals
    }

    return 0;
}

/* OUTPUT
============================================================================
plz check ./13b.c for output
============================================================================
*/