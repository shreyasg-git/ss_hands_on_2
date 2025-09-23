/*
============================================================================
Name : 12.c
Author : Shreyas Gangurde
Description : 12. Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.
Date: 23rd September 2025
============================================================================
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid == 0) {
    printf("Child: PID = %d, Parent PID = %d\n", getpid(), getppid());

    sleep(1);

    printf("Child: Sending SIGKILL to parent (PID = %d)\n", getppid());

    kill(getppid(), SIGKILL);

    sleep(2);
    printf("Child: Now my new parent is PID = %d (init/systemd)\n", getppid());

    for (int i = 0; i < 5; i++) {
      printf("Child: Still alive (iteration %d)\n", i + 1);
      sleep(1);
    }
  } else {
    printf("Parent: PID = %d, Child PID = %d\n", getpid(), pid);
    while (1) {
      sleep(1);
    }
  }

  return 0;
}

/* OUTPUT
============================================================================
(base) shreyasbg@anton~$ cc 12.c -o 1 && ./1
Parent: PID = 19520, Child PID = 19521
Child: PID = 19521, Parent PID = 19520
Child: Sending SIGKILL to parent (PID = 19520)
Killed
(base) shreyasbg@anton~$ Child: Now my new parent is PID = 1932 (init/systemd)
Child: Still alive (iteration 1)
Child: Still alive (iteration 2)
Child: Still alive (iteration 3)
Child: Still alive (iteration 4)
Child: Still alive (iteration 5)
^C
============================================================================
*/