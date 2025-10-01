/*
============================================================================
Name : 29.c
Author : Shreyas Gangurde
Description : 29. Write a program to remove the message queue.
Date: 1st October 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {

  key_t key;
  int msgid;

  key = ftok("msgqprog", 65);

  msgid = msgget(key, 0666);

  msgctl(msgid, IPC_RMID, NULL);
  printf("Message queue removed Successfully.\n");

  return 0;
}
/* OUTPUT
============================================================================
Message queue removed Successfully.
============================================================================
*/