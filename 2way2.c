/**
 * @file process_two.c
 * @brief Establishes non-blocking, two-way communication using two FIFOs and select().
 *
 * This program opens two existing named pipes (FIFOs): myfifo1 and myfifo2.
 * It uses the select() system call to monitor both standard input (for user messages)
 * and the read-end of the FIFO (for incoming messages) at the same time.
 * This allows for asynchronous, non-blocking communication.
 *
 * To run:
 * 1. First, run process_one in a separate terminal to create the FIFOs.
 * 2. Compile: gcc process_two.c -o proc2
 * 3. In the second terminal, run: ./proc2
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
  int fd_read, fd_write;
  char buffer[MAX_BUFFER_SIZE];
  fd_set read_fds;
  int max_fd;

  printf("Process Two is starting...\n");

  // Open FIFO1 for reading. This will block until Process One opens it for writing.
  fd_read = open(FIFO1, O_RDONLY);
  if (fd_read == -1) {
    perror("open read FIFO failed");
    exit(EXIT_FAILURE);
  }

  // Open FIFO2 for writing. This will block until Process One opens it for reading.
  fd_write = open(FIFO2, O_WRONLY);
  if (fd_write == -1) {
    perror("open write FIFO failed");
    exit(EXIT_FAILURE);
  }

  printf("Connection established. You can start chatting.\n");
  printf("Type 'exit' to terminate.\n\n");

  while (1) {
    // Clear the descriptor set and add stdin and the read FIFO
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(fd_read, &read_fds);

    // Find the highest file descriptor number for the select() call
    max_fd = (STDIN_FILENO > fd_read) ? STDIN_FILENO : fd_read;

    // Wait for an activity on one of the file descriptors
    if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) == -1) {
      perror("select");
      break;
    }

    // --- Check for user input from the keyboard ---
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      if (fgets(buffer, MAX_BUFFER_SIZE, stdin) == NULL) {
        // Handle EOF (Ctrl+D) as an exit signal
        printf("Input closed. Sending exit signal.\n");
        strcpy(buffer, "exit\n");
      }

      // Write the user's message to the other process
      if (write(fd_write, buffer, strlen(buffer) + 1) == -1) {
        perror("write failed");
        break;
      }

      // If the user typed "exit", break the loop
      if (strncmp(buffer, "exit", 4) == 0) {
        printf("Exiting...\n");
        break;
      }
    }

    // --- Check for incoming data from the other process ---
    if (FD_ISSET(fd_read, &read_fds)) {
      ssize_t bytes_read = read(fd_read, buffer, MAX_BUFFER_SIZE);
      if (bytes_read <= 0) {
        printf("Process One has disconnected. Exiting.\n");
        break;
      }

      buffer[bytes_read] = '\0'; // Ensure null-termination
      printf("\rProcess One: %s", buffer);
      fflush(stdout); // Ensure the message is printed immediately

      if (strncmp(buffer, "exit", 4) == 0) {
        printf("\rProcess One terminated. Exiting.\n");
        break;
      }
    }
  }

  // Close the file descriptors
  close(fd_read);
  close(fd_write);

  return 0;
}
