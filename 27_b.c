/*
============================================================================
Name : 27_b.c
Author : Shreyas Gangurde
Description : 27. Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
Date: 1st October 2025
============================================================================
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
  long mtype;
  char mtext[100];
};

int main() {

  key_t key;
  int msgid;
  struct msgbuf message;

  key = ftok("msgqprog", 65);
  msgid = msgget(key, 0666);
  message.mtype = 1;
  int flag = IPC_NOWAIT;

  printf("Receiving message with non-blocking ...\n");

  if (msgrcv(msgid, &message, sizeof(message.mtext), message.mtype, flag) == -1) {
    if (errno == ENOMSG) {
      printf("No message available in the message queue!...\n");
    } else {
      perror("msgrcv");
      exit(EXIT_FAILURE);
    }
  } else
    printf("Received (Non-blocking): %s\n", message.mtext);

  return 0;
}
/* OUTPUT
============================================================================
Receiving message with non-blocking ...
Received (Non-blocking): YOYOY
============================================================================
*/