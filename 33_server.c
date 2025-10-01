/*
============================================================================
Name : 33_server.c
Author : Shreyas Gangurde
Description : 33. Write a program to communicate between two machines using socket.
Date: 1st October 2025
============================================================================
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
  int server_fd, new_socket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[BUF_SIZE] = {0};
  char *hello = "Hello from Server";

  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  bind(server_fd, (struct sockaddr *)&address, sizeof(address));

  // Listen for connections

  listen(server_fd, 3);
  printf("Server listening on port %d...\n", PORT);

  // Accept connection
  new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

  read(new_socket, buffer, BUF_SIZE);
  printf("Client: %s\n", buffer);

  send(new_socket, hello, strlen(hello), 0);
  printf("Message sent to client\n");

  close(new_socket);
  close(server_fd);
  return 0;
}
/* OUTPUT
============================================================================
Named semaphore created
Named semaphore removed
============================================================================
*/