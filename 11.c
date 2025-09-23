/*
============================================================================
Name : 11.c
Author : Shreyas Gangurde
Description : 11. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - use sigaction system call.
Date: 23rd September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  struct sigaction sa_ignore, sa_default;

  sa_ignore.sa_handler = SIG_IGN;
  sigemptyset(&sa_ignore.sa_mask);
  sa_ignore.sa_flags = 0;

  sigaction(SIGINT, &sa_ignore, NULL);

  printf("SIGINT is now ignored. Try pressing Ctrl+C...\n");
  sleep(5);

  sa_default.sa_handler = SIG_DFL;
  sigemptyset(&sa_default.sa_mask);
  sa_default.sa_flags = 0;

  sigaction(SIGINT, &sa_default, NULL);
  printf("\nSIGINT is reset to default. Try pressing Ctrl+C again...\n");

  while (1) {
    pause();
  }

  return 0;
}
/* OUTPUT
============================================================================
SIGINT is now ignored. Try pressing Ctrl+C...
^C^C^C^C^C
SIGINT is reset to default. Try pressing Ctrl+C again...
^C
============================================================================
*/