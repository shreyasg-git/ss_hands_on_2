/*
============================================================================
Name : 27_a.c
Author : Shreyas Gangurde
Description : 27. Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
Date: 1st October 2025
============================================================================
*/

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
  int flag = 0;

  printf("Receiving message with blocking (flag 0)...\n");

  msgrcv(msgid, &message, sizeof(message.mtext), message.mtype, flag);

  printf("Received (blocking): %s\n", message.mtext);

  return 0;
}
/* OUTPUT
============================================================================
Receiving message with blocking (flag 0)...
Received (blocking): Hii
============================================================================
*/