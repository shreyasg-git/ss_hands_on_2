/*
============================================================================
Name : 34b.c
Author : Shreyas Gangurde
Description : 34. Write a program to create a concurrent server.
b. use pthread_create
Date: 1st October 2025
============================================================================
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BACKLOG 5
#define BUF_SIZE 1024

void *handle_client(void *arg) {
  int client_fd = *((int *)arg);
  free(arg);

  char buffer[BUF_SIZE];
  memset(buffer, 0, BUF_SIZE);

  int n = recv(client_fd, buffer, BUF_SIZE - 1, 0);
  if (n > 0) {
    printf("Received from client: %s\n", buffer);
    send(client_fd, "Hello from threaded server!\n", 28, 0);
  }

  close(client_fd);
  pthread_exit(NULL);
}

int main() {
  int sockfd, new_fd;
  struct sockaddr_in server_addr, client_addr;
  socklen_t sin_size;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  int opt = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  memset(&(server_addr.sin_zero), '\0', 8);

  bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

  listen(sockfd, BACKLOG);

  printf("Server listening on port %d...\n", PORT);

  while (1) {
    sin_size = sizeof(struct sockaddr_in);
    new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
    if (new_fd == -1) {
      perror("accept");
      continue;
    }

    printf("Server: got connection from %s\n", inet_ntoa(client_addr.sin_addr));

    int *client_fd = malloc(sizeof(int));
    *client_fd = new_fd;

    pthread_t tid;
    pthread_create(&tid, NULL, handle_client, client_fd);

    pthread_detach(tid);
  }

  close(sockfd);
  return 0;
}

/* OUTPUT
============================================================================
Server listening on port 8080...
Server: got connection from 127.0.0.1
Server: got connection from 127.0.0.1
Server: got connection from 127.0.0.1
Server: got connection from 127.0.0.1
Server: got connection from 127.0.0.1
Received from client: Hello from client 1
Received from client: Hello from client 2
Received from client: Hello from client 3
Received from client: Hello from client 4
Received from client: Hello from client 5
============================================================================

============================================================================
(base) shreyasbg@anton~$ nc localhost 8080
Hello from client 1
Hello from threaded server!
============================================================================

============================================================================
(base) shreyasbg@anton~$ nc localhost 8080
Hello from client 2
Hello from threaded server!
============================================================================

============================================================================
(base) shreyasbg@anton~$ nc localhost 8080
Hello from client 3
Hello from threaded server!
============================================================================

============================================================================
(base) shreyasbg@anton~$ nc localhost 8080
Hello from client 4
Hello from threaded server!
============================================================================

============================================================================
(base) shreyasbg@anton~$ nc localhost 8080
Hello from client 5
Hello from threaded server!
============================================================================

*/