/*
============================================================================
Name : 8b.c
Author : Shreyas Gangurde
Description : 8. Write a separate program using signal system call to catch the following signals.
                  b. SIGINT
Date: 20th September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_handler(int signo) {
  if (signo == SIGINT)
    printf("received SIGINT\n");
}

int main(void) {
  signal(SIGINT, sig_handler);

  while (1)
    sleep(1);
  return 0;
}

/* OUTPUT
============================================================================
^Creceived SIGINT
^Creceived SIGINT
^Creceived SIGINT
^Z
[2]+  Stopped                 ./temp
============================================================================
*/