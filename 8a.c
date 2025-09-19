/*
============================================================================
Name : 8a.c
Author : Shreyas Gangurde
Description : 8. Write a separate program using signal system call to catch the following signals.
                  a. SIGSEGV
Date: 12th September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigsegv_handler(int signo) {
  printf("Caught signal %d (SIGSEGV): Segmentation fault occurred!\n", signo);
  exit(1);
}

int main() {
  signal(SIGSEGV, sigsegv_handler);

  printf("Raising a segmentation fault intentionally...\n");

  int *ptr = NULL;
  *ptr = 117;

  printf("This line will not execute.\n");

  return 0;
}

/* OUTPUT
============================================================================
Raising a segmentation fault intentionally...
Caught signal 11 (SIGSEGV): Segmentation fault occurred!
============================================================================
*/