/*
============================================================================
Name : 25.c
Author : Shreyas Gangurde
Description : 25. Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
Date: 1st October 2025
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main() {

  key_t key;
  int msgid;
  struct msqid_ds buf;

  key = ftok("msgqprog", 'a');

  msgid = msgget(key, IPC_CREAT | 0766);

  msgctl(msgid, IPC_STAT, &buf);

  printf("Message queue ID: %d\n", msgid);

  printf("Access permissions: %o\n", buf.msg_perm.mode & 0777);

  printf("Owner UID: %d\n", buf.msg_perm.uid);
  printf("Owner GID: %d\n", buf.msg_perm.gid);
  printf("Creator UID: %d\n", buf.msg_perm.cuid);
  printf("Creator UID: %d\n", buf.msg_perm.cgid);

  printf("Time of last msg sent: %s", ctime(&buf.msg_stime));
  printf("Time of last msg received: %s", ctime(&buf.msg_rtime));

  printf("Time of last change in message queue: %s", ctime(&buf.msg_ctime));

  printf("Current size of deque: %ld bytes\n", buf.msg_cbytes);

  printf("Number of messages in queue: %ld\n", buf.msg_qnum);

  printf("Maximum bytes allowed in queue: %ld\n", buf.msg_qbytes);

  printf("PID of last msgsnd: %d\n", buf.msg_lspid);
  printf("PID of last msgrcv: %d\n", buf.msg_lrpid);

  return 0;
}
/* OUTPUT
============================================================================
Message queue ID: -1
Access permissions: 0
Owner UID: 0
Owner GID: 1
Creator UID: 0
Creator UID: 1
Time of last msg sent: Thu Jan  1 06:03:52 1970
Time of last msg received: Thu Jun 23 11:13:37 4461453
Time of last change in message queue: Thu Jul 18 06:48:56 3969354
Current size of deque: 1103823372288 bytes
Number of messages in queue: 2
Maximum bytes allowed in queue: 3219913727
PID of last msgsnd: -1192444903
PID of last msgrcv: 32765
============================================================================
*/