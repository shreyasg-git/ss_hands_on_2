/*
============================================================================
Name : 8g.c
Author : Shreyas Gangurde
Description : 8. Write a separate program using signal system call to catch
              the following signals: g. SIGPROF (use setitimer system call)
Date: 20th September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void sig_handler(int signo) {
  printf("received SIGPROF. Exiting.\n");
  exit(0);
}

int main(void) {
  struct itimerval timer;

  signal(SIGPROF, sig_handler);

  timer.it_value.tv_sec = 2;
  timer.it_value.tv_usec = 0;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 0;

  setitimer(ITIMER_PROF, &timer, NULL);

  printf("Timer started. Waiting for signals...\n");

  while (1) {
  }

  return 0;
}
/* OUTPUT
============================================================================
Timer started. Waiting for signals...
received SIGPROF. Exiting.
============================================================================
*/
