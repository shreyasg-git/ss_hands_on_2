/*
============================================================================
Name : 19d.c
Author : Shreyas Gangurde
Description : 19. Create a FIFO file by
                d. mknod system call
Date: 23rd September 2025
============================================================================
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
  int fd;
  char buffer[BUFFER_SIZE];

  mkfifo("myfifo", 0666);

  fd = open("myfifo", O_RDONLY | O_NONBLOCK);

  fd_set read_fds;
  struct timeval timeout;

  FD_ZERO(&read_fds);
  FD_SET(fd, &read_fds);

  timeout.tv_sec = 10;
  timeout.tv_usec = 0;

  printf("Waiting for data on FIFO '%s' for 10 seconds...\n", "myfifo");

  int ret = select(fd + 1, &read_fds, NULL, NULL, &timeout);

  if (ret == -1) {
    perror("select");
    close(fd);
    exit(EXIT_FAILURE);
  } else if (ret == 0) {
    printf("Timeout: No data received within 10 seconds.\n");
  } else {
    if (FD_ISSET(fd, &read_fds)) {
      int bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
      if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Received data: %s\n", buffer);
      } else if (bytes_read == 0) {
        printf("FIFO closed by writer.\n");
      } else {
        perror("read");
      }
    }
  }

  close(fd);
  return 0;
}

/* OUTPUT
============================================================================
(base) shreyasbg@anton~$ cc 22.c -o temp && ./temp
Waiting for data on FIFO 'myfifo' for 10 seconds...
Timeout: No data received within 10 seconds.


(base) shreyasbg@anton~$ cc 22.c -o temp && ./temp
Waiting for data on FIFO 'myfifo' for 10 seconds...
Received data: yo
============================================================================

TERMINAL 2
============================================================================
(base) shreyasbg@anton~$ echo "yo" > myfifo
============================================================================
*/