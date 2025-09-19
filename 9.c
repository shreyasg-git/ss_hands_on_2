/*
============================================================================
Name : 9.c
Author : Shreyas Gangurde
Description : 9. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - Use signal system call.
Date: 12th September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  printf("Step 1: Ignoring SIGINT (try pressing Ctrl+C now)...\n");
  signal(SIGINT, SIG_IGN);

  sleep(5);

  printf("\nStep 2: Restoring default action for SIGINT.\n");

  signal(SIGINT, SIG_DFL);

  sleep(5);

  printf("\nIf you didn't press Ctrl+C, program exits normally.\n");

  return 0;
}

/* OUTPUT
============================================================================
Step 1: Ignoring SIGINT (try pressing Ctrl+C now)...
^C^C^C^C^C
Step 2: Restoring default action for SIGINT.

If you didn't press Ctrl+C, program exits normally.
============================================================================
*/
