/*
============================================================================
Name : 31b.c
Author : Shreyas Gangurde
Description : 31. Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
Date: 1st October 2025
============================================================================
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  sem_t counting_sem;

  sem_init(&counting_sem, 0, 5);

  printf("Counting semaphore created and initialized to 5\n");

  sem_destroy(&counting_sem);

  return 0;
}
/* OUTPUT
============================================================================
Counting semaphore created and initialized to 5
============================================================================
*/