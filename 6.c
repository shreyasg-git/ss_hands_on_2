/*
============================================================================
Name : 6.c
Author : Shreyas Gangurde
Description : 6. Write a simple program to create three threads.
Date: 12th September 2025
============================================================================
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *my_thread_function(void *arg) {
  char *message = (char *)arg;
  printf("Thread started: %s\n", message);
  sleep(1);
  printf("Thread finished: %s\n", message);
  pthread_exit(NULL);
}

int main() {
  pthread_t thread1_id, thread2_id, thread3_id;

  char *msg1 = "Thread 1";
  char *msg2 = "Thread 2";
  char *msg3 = "Thread 3";

  int ret1 = pthread_create(&thread1_id, NULL, my_thread_function, (void *)msg1);

  int ret2 = pthread_create(&thread2_id, NULL, my_thread_function, (void *)msg2);

  int ret3 = pthread_create(&thread3_id, NULL, my_thread_function, (void *)msg3);

  printf("MAIN :: Waiting for threads...\n");

  pthread_join(thread1_id, NULL);
  pthread_join(thread2_id, NULL);
  pthread_join(thread3_id, NULL);

  printf("MAIN :: All Threads Returned\n");

  return 0;
}

/* OUTPUT
============================================================================
MAIN :: Waiting for threads...
Thread started: Thread 1
Thread started: Thread 3
Thread started: Thread 2
Thread finished: Thread 1
Thread finished: Thread 2
Thread finished: Thread 3
MAIN :: All Threads Returned

============================================================================
*/