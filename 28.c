/*
============================================================================
Name : 28.c
Author : Shreyas Gangurde
Description : 28. Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 1st October 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {

  key_t key;
  int msgid;
  struct msqid_ds buf;

  key = ftok("msgqprog", 65);
  msgid = msgget(key, 0666);

  msgctl(msgid, IPC_STAT, &buf);
  printf("Old permissions: %o\n", buf.msg_perm.mode & 0777);

  // change permission to new value
  if ((buf.msg_perm.mode & 0777) == 0666)
    buf.msg_perm.mode = 0644;
  else
    buf.msg_perm.mode = 0666;

  msgctl(msgid, IPC_SET, &buf);

  printf("New permissions: %o\n", buf.msg_perm.mode & 0777);

  return 0;
}

/* OUTPUT
============================================================================
Old permissions: 666
New permissions: 644
============================================================================
*/