/*
============================================================================
Name : 7.c
Author : Shreyas Gangurde
Description : 7. Write a simple program to print the created thread ids..
Date: 20th September 2025
============================================================================
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <unistd.h>

void *my_thread_function() {

  printf("[THREAD] started thread with ID: %d\n", gettid());
  sleep(1);
  printf("[THREAD] done with thread with ID: %d\n", gettid());
  pthread_exit(NULL);
}

int main() {
  pthread_t thread1_id, thread2_id, thread3_id;

  char *msg1 = "Thread 1";
  char *msg2 = "Thread 2";
  char *msg3 = "Thread 3";

  int ret1 = pthread_create(&thread1_id, NULL, my_thread_function, NULL);

  int ret2 = pthread_create(&thread2_id, NULL, my_thread_function, NULL);

  int ret3 = pthread_create(&thread3_id, NULL, my_thread_function, NULL);

  printf("MAIN :: Waiting for threads...\n");

  pthread_join(thread1_id, NULL);
  pthread_join(thread2_id, NULL);
  pthread_join(thread3_id, NULL);

  printf("MAIN :: All Threads Returned.\n");

  return 0;
}

/* OUTPUT
============================================================================
MAIN :: Waiting for threads...
[THREAD] started thread with ID: 39226
[THREAD] started thread with ID: 39227
[THREAD] started thread with ID: 39228
[THREAD] done with thread with ID: 39226
[THREAD] done with thread with ID: 39227
[THREAD] done with thread with ID: 39228
MAIN :: All Threads Returned.
============================================================================
*/