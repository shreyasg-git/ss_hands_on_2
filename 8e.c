/*
============================================================================
Name : 8e.c
Author : Shreyas Gangurde
Description : 8. Write a separate program using signal system call to catch the following signals.
                  e. SIGALRM (use setitimer system call)
Date: 12th September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void sig_handler(int signo) {
  printf("received SIGALRM. Exiting.\n");
  exit(1);
}

int main(void) {

  struct itimerval timer;

  signal(SIGALRM, sig_handler);

  timer.it_value.tv_sec = 2;
  timer.it_value.tv_usec = 10;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 0;

  setitimer(ITIMER_REAL, &timer, NULL);

  printf("Timer started. Waiting for signals...\n");

  // pause until we receive a signal
  pause();

  return 0;
}

/* OUTPUT
============================================================================
Timer started. Waiting for signals...
received SIGALRM. Exiting.
============================================================================
*/