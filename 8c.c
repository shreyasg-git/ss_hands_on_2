/*
============================================================================
Name : 8c.c
Author : Shreyas Gangurde
Description : 8. Write a separate program using signal system call to catch the following signals.
                  c. SIGFPE
Date: 12th September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int signo) {
  printf("received SIGFPE. Exiting.\n");
  exit(1);
}

int main(void) {
  signal(SIGFPE, sig_handler);

  int a = 10;
  int b = 0;

  int c = a / b;

  printf("Unreachable Code.");

  return 0;
}

/* OUTPUT
============================================================================
received SIGFPE. Exiting.

============================================================================
*/