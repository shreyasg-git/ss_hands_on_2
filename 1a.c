/*
============================================================================
Name : 1a.c
Author : Shreyas Gangurde
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
                  a. ITIMER_REAL
Date: 10th September 2025
============================================================================
*/

// ITIMER_REAL- real clock
// ITIMER_VIRTUAL - count only when the process is actively running
// ITIMER_PROF - ccount when the process is running and also when kernel is doing some work on behalf of the process

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void alarm_handler(int signum) {
  printf("ITIMER_REAL fired\n");
  exit(0);
}

int main() {
  struct itimerval timer;

  if (signal(SIGALRM, alarm_handler) == SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }

  timer.it_value.tv_sec = 10;
  timer.it_value.tv_usec = 10;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 0;

  if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
    perror("setitimer");
    exit(EXIT_FAILURE);
  }

  printf("Timer started. Waiting for signals...\n");

  // pause until we receive a signal
  pause();

  return 0;
}

/* OUTPUT
============================================================================
Timer started. Waiting for signals...
ITIMER_REAL fired
============================================================================
*/
