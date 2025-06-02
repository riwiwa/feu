#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <curl/curl.h>

#define PORT 9292
#define IP "127.0.0.1"
#define LISTEN_BACKLOG 50
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)
#define MAX_FILE_SIZE 50000

int main(void)
{
  int socket_fd, client_fd;
  socklen_t client_addr_size; 
  struct sockaddr_in server_addr, client_addr;

  if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    handle_error("socket");
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(PORT);

  if(bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
  {
    handle_error("bind");
  }

  if(listen(socket_fd, LISTEN_BACKLOG) == -1)
  {
    handle_error("listen");
  }

  client_addr_size = sizeof(client_addr);
  FILE *client_file = fopen("client_file", "w+");
  int client_ch;
  printf("Waiting for client\n");
  client_fd = accept(socket_fd, (struct sockaddr *) &client_addr, &client_addr_size);
  printf("Client connected!\n");
  if(client_fd == -1)
  {
    handle_error("accept");
  }
  int ack = 1;
  while(1)
  {
    
    if((recv(client_fd, &client_ch, MAX_FILE_SIZE, 0)) <= 0)
    {
      break;
    }
    fputc(client_ch, client_file);
    send(client_fd, &ack, sizeof(ack), 0);
  }
  printf("File recieved\n");
 
  if(close(socket_fd) == -1)
  {
    handle_error("close");
  }

  return 0;
}
