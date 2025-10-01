/*
============================================================================
Name : 32b.c
Author : Shreyas Gangurde
Description : 32. Write a program to implement semaphore to protect any critical section.
b. protect shared memory from concurrent write access
Date: 1st October 2025
============================================================================
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 4
char shared_buffer[100];
sem_t sem;

void *write_shared(void *arg) {
  sem_wait(&sem);

  snprintf(shared_buffer, sizeof(shared_buffer), "Thread %ld wrote this message.", (long)pthread_self());
  printf("%s\n", shared_buffer);

  sem_post(&sem);
  return NULL;
}

int main() {
  pthread_t threads[NUM_THREADS];
  sem_init(&sem, 0, 1);

  for (int i = 0; i < NUM_THREADS; i++)
    pthread_create(&threads[i], NULL, write_shared, NULL);

  for (int i = 0; i < NUM_THREADS; i++)
    pthread_join(threads[i], NULL);

  sem_destroy(&sem);
  return 0;
}

/* OUTPUT
============================================================================
Thread 140341216802368 wrote this message.
Thread 140341208409664 wrote this message.
Thread 140341076293184 wrote this message.
Thread 140341200016960 wrote this message.
============================================================================
*/