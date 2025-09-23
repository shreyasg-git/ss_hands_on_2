/*
============================================================================
Name : 13b.c
Author : Shreyas Gangurde
Description : 13. Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.
Date: 23rd September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  pid_t pid = atoi(argv[1]);

  kill(pid, SIGSTOP);

  printf("Sent SIGSTOP to process %d\n", pid);
  return 0;
}

/* OUTPUT

TERMINAL 1
============================================================================
(base) shreyasbg@anton~$ cc 13a.c -o 1 && ./1
Process PID = 20365
Waiting for signals (try sending SIGSTOP)...

[2]+  Stopped                 ./1
============================================================================

TERMINAL 2
============================================================================
(base) shreyasbg@anton~$ cc 13b.c -o 13b && ./13b 20365
Sent SIGSTOP to process 20365

============================================================================


*/