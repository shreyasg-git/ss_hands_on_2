/*
============================================================================
Name : 32a.c
Author : Shreyas Gangurde
Description : 32. Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
Date: 1st October 2025
============================================================================
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

int ticket = 0;
sem_t sem;

void *issue_ticket(void *arg) {
  sem_wait(&sem);

  ticket++;
  printf("Thread %ld issued ticket #%d\n", (long)pthread_self(), ticket);

  sem_post(&sem);
  return NULL;
}

int main() {
  pthread_t threads[NUM_THREADS];
  sem_init(&sem, 0, 1);

  for (int i = 0; i < NUM_THREADS; i++)
    pthread_create(&threads[i], NULL, issue_ticket, NULL);

  for (int i = 0; i < NUM_THREADS; i++)
    pthread_join(threads[i], NULL);

  sem_destroy(&sem);
  return 0;
}
/* OUTPUT
============================================================================
Thread 129242434106944 issued ticket #1
Thread 129242408928832 issued ticket #2
Thread 129242425714240 issued ticket #3
Thread 129242417321536 issued ticket #4
Thread 129242400536128 issued ticket #5

============================================================================
*/