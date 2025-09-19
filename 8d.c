/*
============================================================================
Name : 8d.c
Author : Shreyas Gangurde
Description : 8. Write a separate program using signal system call to catch the following signals.
                  d. SIGALRM (use alarm system call)
Date: 12th September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int signo) {
  printf("received SIGALRM. Exiting.\n");
  exit(1);
}

int main(void) {

  signal(SIGALRM, sig_handler);

  printf("Upcoming Alarm in 2 seconds\n");

  unsigned int wait = 2;

  alarm(wait);

  while (1)
    sleep(1);

  return 0;
}

/* OUTPUT
============================================================================
Upcoming Alarm in 2 seconds
received SIGALRM. Exiting.

============================================================================
*/