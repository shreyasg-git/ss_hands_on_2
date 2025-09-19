/*
============================================================================
Name : 10b.c
Author : Shreyas Gangurde
Description : 10. Write a separate program using sigaction system call to catch the following signals.
                  b. SIGINT
Date: 20th September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int signo, siginfo_t *info, void *context) {
  printf("Caught signal %d (SIGINT)\n", signo);
  exit(1);
}

int main() {
  struct sigaction sa;

  sa.sa_sigaction = sigint_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_SIGINFO;

  sigaction(SIGINT, &sa, NULL);

  printf("Press Ctrl + C to raise a signal...\n");

  while (1) {
  }

  return 0;
}

/* OUTPUT
============================================================================
Press Ctrl + C to raise a signal...
^CCaught signal 2 (SIGINT)
============================================================================
*/
