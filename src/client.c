#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <curl/curl.h>

#define PORT 9292
#define IP "127.0.0.1"
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while(0)

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    printf("ERROR: Specify 1 file to be sent\n");
    return -1;
  }
  int server_fd;
  FILE *file = fopen(argv[1], "r+");
  if(file == NULL)
  {
    printf("ERROR: Couldn't open file\n");
    return -1;
  }
  struct sockaddr_in server_addr;

  if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    handle_error("socket");
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(PORT);

  if(connect(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
  {
    handle_error("connect");
  }

  char *buf = 0;
  long len;
  int ack;

  fseek(file, 0, SEEK_END);
  len = ftell(file);
  fseek(file, 0, SEEK_SET);
  buf = malloc(len);

  char c[len];

  fread(buf, 1, len, file);
  
  strcpy(c, buf);
  for(int i = 0; i < len; i++)
  {
    send(server_fd, &c[i], sizeof(c[i]), 0);
    recv(server_fd, &ack, 500, 0);
    if(ack != 1)
    {
      break;
    }
  }

  printf("File sent!\n");
 
  if(close(server_fd) == -1)
  {
    handle_error("close");
  }

  return 0;
}
