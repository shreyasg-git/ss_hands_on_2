/*
============================================================================
Name : 21a.c
Author : Shreyas Balasaheb Gangurde
Description :21. Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 23rd September 2025
============================================================================
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO1 "myfifo1"
#define FIFO2 "myfifo2"
#define MAX_BUFFER_SIZE 1024

int main() {
  int fd_write, fd_read;
  char buffer[MAX_BUFFER_SIZE];
  fd_set read_fds;
  int max_fd;

  mkfifo(FIFO1, 0666);

  mkfifo(FIFO2, 0666);

  printf("Process One is ready. Waiting for Process Two...\n");

  // this will block until Process Two opens it for reading.
  fd_write = open(FIFO1, O_WRONLY);

  // this will block until Process Two opens it for writing.
  fd_read = open(FIFO2, O_RDONLY);

  printf("Connection established. You can start chatting.Type 'exit' to terminate.\n\n");

  while (1) {
    // Clear the descriptor set and add stdin and the read FIFO
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(fd_read, &read_fds);

    // Find the highest file descriptor number for the select() call
    max_fd = (STDIN_FILENO > fd_read) ? STDIN_FILENO : fd_read;

    // Wait for an activity on one of the file descriptors
    select(max_fd + 1, &read_fds, NULL, NULL, NULL);

    // outgoing
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      if (fgets(buffer, MAX_BUFFER_SIZE, stdin) == NULL) {
        // Handle EOF (Ctrl+D) as an exit signal
        printf("Input closed. Sending exit signal.\n");
        strcpy(buffer, "exit\n");
      }

      // Write the user's message to the other process
      write(fd_write, buffer, strlen(buffer) + 1);

      // If the user typed "exit", break the loop
      if (strncmp(buffer, "exit", 4) == 0) {
        printf("Exiting...\n");
        break;
      }
    }

    // incoming check
    if (FD_ISSET(fd_read, &read_fds)) {
      ssize_t bytes_read = read(fd_read, buffer, MAX_BUFFER_SIZE);
      if (bytes_read <= 0) {
        printf("Process Two has disconnected. Exiting.\n");
        break;
      }

      buffer[bytes_read] = '\0';
      printf("\rProcess Two: %s", buffer);
      fflush(stdout);

      if (strncmp(buffer, "exit", 4) == 0) {
        printf("\rProcess Two terminated. Exiting.\n");
        break;
      }
    }
  }

  close(fd_write);
  close(fd_read);

  unlink(FIFO1);
  unlink(FIFO2);

  return 0;
}
/* OUTPUT TERMINAL 1
============================================================================
Process One is ready. Waiting for Process Two...
Connection established. You can start chatting.Type 'exit' to terminate.

Process Two: HEllo
Hi Whatsuppp
Process Two: nohing much
Process Two: exit
Process Two terminated. Exiting.
============================================================================

OUTPUT TERMINAL 2
============================================================================
Process Two is starting...
Connection established. You can start chatting.
Type 'exit' to terminate.

HEllo
Process One: Hi Whatsuppp
nohing much
exit
Exiting...
============================================================================

*/