/*
============================================================================
Name : 32d.c
Author : Shreyas Gangurde
Description : 32. Write a program to implement semaphore to protect any critical section.
d. remove the created semaphore
Date: 1st October 2025
============================================================================
*/

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  sem_t *sem;

  sem = sem_open("/mysem", O_CREAT, 0644, 1);

  printf("Named semaphore created\n");

  sem_close(sem);
  sem_unlink("/mysem");

  printf("Named semaphore removed\n");
  return 0;
}
/* OUTPUT
============================================================================
Named semaphore created
Named semaphore removed
============================================================================
*/