#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 9292
#define IP "127.0.0.1"

int main(int argc, char *argv[])
{
  struct sockaddr_in  addr;
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(PORT);

  if(bind(socket_fd, (struct sockaddr *) &addr, sizeof(addr)))
  {
    printf("ERROR: Failed to bind to address: %d:%d", IP, PORT);
  }

  if(listen(socket_fd, 10000) == -1)
  {
    printf("ERROR: Failed to listen on address: %d:%d", IP, PORT);
  }

  return 0;
}
