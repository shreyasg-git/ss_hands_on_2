/*
============================================================================
Name : 10c.c
Author : Shreyas Gangurde
Description : 10. Write a separate program using sigaction system call to catch the following signals.
                  c. SIGFPE
Date: 12th September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigfpe_handler(int signo, siginfo_t *info, void *context) {
  printf("Caught signal %d (SIGFPE)\n", signo);

  switch (info->si_code) {
  case FPE_INTDIV:
    printf("[ERROR] :: Integer divide by zero\n");
    break;
  case FPE_INTOVF:
    printf("[ERROR] :: Integer overflow\n");
    break;
  case FPE_FLTDIV:
    printf("[ERROR] :: Floating-point divide by zero\n");
    break;
  case FPE_FLTOVF:
    printf("[ERROR] :: Floating-point overflow\n");
    break;
  case FPE_FLTUND:
    printf("[ERROR] :: Floating-point underflow\n");
    break;
  case FPE_FLTRES:
    printf("[ERROR] :: Floating-point inexact result\n");
    break;
  case FPE_FLTINV:
    printf("[ERROR] :: Floating-point invalid operation\n");
    break;
  case FPE_FLTSUB:
    printf("[ERROR] :: Subscript out of range\n");
    break;
  default:
    printf("[ERROR] :: Unknown FPE code %d\n", info->si_code);
    break;
  }

  exit(1);
}

int main() {
  struct sigaction sa;

  sa.sa_sigaction = sigfpe_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_SIGINFO;

  sigaction(SIGFPE, &sa, NULL);

  int a = 10;
  int b = 0;

  int c = a / b;

  printf("Unreachable Code.");

  return 0;
}

/* OUTPUT
============================================================================
Caught signal 8 (SIGFPE)
[ERROR] :: Integer divide by zero
============================================================================
*/
