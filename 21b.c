#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd_write, fd_read;
  char *sendfifo = "/tmp/fifo2"; // B writes to fifo2
  char *recfifo = "/tmp/fifo1";  // B reads from fifo1

  // Create FIFOs if not already there
  mkfifo(sendfifo, 0666);
  mkfifo(recfifo, 0666);

  char buf[80];

  printf("Program B starting...\n");
  fflush(stdout);

  // Open with O_RDWR to avoid blocking
  fd_write = open(sendfifo, O_RDWR);
  fd_read = open(recfifo, O_RDWR);

  if (fd_write < 0 || fd_read < 0) {
    perror("open");
    exit(1);
  }

  printf("Program B connected.\n");
  fflush(stdout);

  while (1) {
    // Read from A
    if (read(fd_read, buf, sizeof(buf)) > 0) {
      printf("[Program A] :: %s", buf);
      fflush(stdout);
    }

    // Write to A
    if (fgets(buf, sizeof(buf), stdin) != NULL) {
      write(fd_write, buf, strlen(buf) + 1);
    }
  }
}
