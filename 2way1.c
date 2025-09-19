/**
 * @file process_one.c
 * @brief Establishes non-blocking, two-way communication using two FIFOs and select().
 *
 * This program creates two named pipes (FIFOs): myfifo1 and myfifo2.
 * It uses the select() system call to monitor both standard input (for user messages)
 * and the read-end of the FIFO (for incoming messages) at the same time.
 * This allows for asynchronous, non-blocking communication.
 *
 * To run:
 * 1. Compile: gcc process_one.c -o proc1
 * 2. In one terminal, run: ./proc1
 * 3. In a second terminal, compile and run process_two.
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

  // Create the two FIFOs
  // The 0666 permission allows read/write access to all users.
  if (mkfifo(FIFO1, 0666) == -1) {
    perror("mkfifo FIFO1 failed");
  }
  if (mkfifo(FIFO2, 0666) == -1) {
    perror("mkfifo FIFO2 failed");
  }

  printf("Process One is ready. Waiting for Process Two...\n");

  // Open FIFO1 for writing. This will block until Process Two opens it for reading.
  fd_write = open(FIFO1, O_WRONLY);
  if (fd_write == -1) {
    perror("open write FIFO failed");
    exit(EXIT_FAILURE);
  }

  // Open FIFO2 for reading. This will block until Process Two opens it for writing.
  fd_read = open(FIFO2, O_RDONLY);
  if (fd_read == -1) {
    perror("open read FIFO failed");
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
        printf("Process Two has disconnected. Exiting.\n");
        break;
      }

      buffer[bytes_read] = '\0'; // Ensure null-termination
      printf("\rProcess Two: %s", buffer);
      fflush(stdout); // Ensure the message is printed immediately

      if (strncmp(buffer, "exit", 4) == 0) {
        printf("\rProcess Two terminated. Exiting.\n");
        break;
      }
    }
  }

  // Close the file descriptors
  close(fd_write);
  close(fd_read);

  // Remove the FIFOs from the filesystem
  unlink(FIFO1);
  unlink(FIFO2);

  return 0;
}
