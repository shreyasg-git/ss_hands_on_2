/*
============================================================================
Name : 1b.c
Author : Shreyas Gangurde
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
                  b. ITIMER_VIRTUAL
Date: 10th September 2025
============================================================================
*/

// ITIMER_REAL- proper clock
// ITIMER_VIRTUAL - count only when the process is actively running
// ITIMER_PROF - ccount when the process is running and also when kernel is doing some work on behalf of the process
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void alarm_handler(int signum) {
  printf("ITIMER_VIRTUAL fired\n");
  exit(0);
}

int main() {
  struct itimerval timer;

  if (signal(SIGVTALRM, alarm_handler) == SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }

  timer.it_value.tv_sec = 10;
  timer.it_value.tv_usec = 10;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 0;

  // 5 seconds - in user mode
  if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
    perror("setitimer");
    exit(EXIT_FAILURE);
  }

  printf("Timer started. Waiting for signals...\n");

  // busy work - process needs to be in running state for the clock to run
  while (1) {
    for (volatile long i = 0; i < 1000000; i++)
      // busy work but in kernel space
      getpid();
    ;
  }

  return 0;
}

/* OUTPUT
============================================================================
Timer started. Waiting for signals...
ITIMER_VIRTUAL fired
============================================================================
*/