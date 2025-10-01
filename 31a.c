/*
============================================================================
Name : 31a.c
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
  sem_t binary_sem;

  sem_init(&binary_sem, 0, 1);

  printf("Binary semaphore created and initialized to 1\n");

  sem_destroy(&binary_sem);

  return 0;
}

/* OUTPUT
============================================================================
Binary semaphore created and initialized to 1
============================================================================
*/