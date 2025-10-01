/*
============================================================================
Name : 32c.c
Author : Shreyas Gangurde
Description : 32. Write a program to implement semaphore to protect any critical section.
c. protect multiple pseudo resources ( may be two) using counting semaphore
Date: 1st October 2025
============================================================================
*/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 6

sem_t printer_sem;

void *use_printer(void *arg) {
  sem_wait(&printer_sem);

  printf("Thread %ld is using a printer...\n", (long)pthread_self());
  sleep(2);
  printf("Thread %ld finished printing.\n", (long)pthread_self());

  sem_post(&printer_sem);
  return NULL;
}

int main() {
  pthread_t threads[NUM_THREADS];

  sem_init(&printer_sem, 0, 2);

  for (int i = 0; i < NUM_THREADS; i++)
    pthread_create(&threads[i], NULL, use_printer, NULL);

  for (int i = 0; i < NUM_THREADS; i++)
    pthread_join(threads[i], NULL);

  sem_destroy(&printer_sem);
  return 0;
}

/* OUTPUT
============================================================================
Thread 124290802382400 is using a printer...
Thread 124290777204288 is using a printer...
Thread 124290802382400 finished printing.
Thread 124290777204288 finished printing.
Thread 124290793989696 is using a printer...
Thread 124290649290304 is using a printer...
Thread 124290793989696 finished printing.
Thread 124290785596992 is using a printer...
Thread 124290649290304 finished printing.
Thread 124290768811584 is using a printer...
Thread 124290785596992 finished printing.
Thread 124290768811584 finished printing.
============================================================================
*/