/*
============================================================================
Name : 24.c
Author : Shreyas Gangurde
Description : 24. Write a program to create a message queue and print the key and message queue id.
Date: 1st October 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {

  key_t key, key2;
  int msgid, msgid2;

  key = ftok("msgqprog", 65);
  key2 = ftok("02.c", 66);

  msgid = msgget(key, IPC_CREAT | 0666);
  msgid2 = msgget(key2, IPC_CREAT | 0666);

  printf("key: %ld\n", (long)key);
  printf("Key in hex: 0x%0x\n", key);
  printf("Message queue ID: %d\n", msgid);

  printf("key2: %ld\n", (long)key2);
  printf("Key2 in hex: 0x%0x\n", key2);
  printf("Message queue ID: %d\n", msgid2);

  return 0;
}

/* OUTPUT
============================================================================
key: -1
Key in hex: 0xffffffff
Message queue ID: 0
key2: -1
Key2 in hex: 0xffffffff
Message queue ID: 0
============================================================================
*/
