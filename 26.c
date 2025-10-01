/*
============================================================================
Name : 26.c
Author : Shreyas Gangurde
Description : 26. Write a program to send messages to the message queue. Check $ipcs -q
Date: 1st October 2025
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

  msgid = msgget(key, IPC_CREAT | 0666);

  message.mtype = 1;
  printf("Enter message: ");
  fgets(message.mtext, sizeof(message.mtext), stdin);

  msgsnd(msgid, &message, strlen(message.mtext) + 1, 0);

  printf("Message sent successfully!\n");

  return 0;
}

/* OUTPUT
============================================================================
Enter message: Hii
Message sent successfully!

============================================================================
*/