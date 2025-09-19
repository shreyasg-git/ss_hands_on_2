/*
============================================================================
Name : 10a.c
Author : Shreyas Gangurde
Description : 10. Write a separate program using sigaction system call to catch the following signals.
                  a. SIGSEGV
Date: 12th September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigsegv_handler(int signo, siginfo_t *info, void *context) {
  printf("Caught signal %d (SIGSEGV)\n", signo);
  printf("Fault address: %p\n", info->si_addr);
  exit(1);
}

int main() {
  struct sigaction sa;

  sa.sa_sigaction = sigsegv_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_SIGINFO;

  sigaction(SIGSEGV, &sa, NULL);

  printf("Triggering a segmentation fault...\n");

  int *ptr = 6767;
  *ptr = 123;
  printf("This will never be printed.\n");

  return 0;
}

/* OUTPUT
============================================================================
Triggering a segmentation fault...
Caught signal 11 (SIGSEGV)
Fault address: 0x1a6f
============================================================================
*/
