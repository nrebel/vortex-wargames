#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 256
#define NO_OF_BYTES 16   // 16 = 4 * sizeof(uint32_t) = 16 bytes. recv returns the number of bytes received

int main(int argc, char *argv[])
{
  int sockfd, port, n;
  struct sockaddr_in server;
  uint32_t sum, *data;
  char buffer[BUFFER_SIZE];
  
  if (argc < 3) {
    fprintf(stderr,"usage: %s <host ip> <port>\n", argv[0]);
    return 1;
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
  server.sin_addr.s_addr = inet_addr(argv[1]);

  inet_pton(AF_INET, argv[1], &server.sin_addr.s_addr);
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  connect(sockfd,(struct sockaddr *)&server,sizeof(server));
  perror("connect(): ");
  
  int count = 0;
  while (count < NO_OF_BYTES) { 
    if ((n = recv(sockfd, buffer + count, sizeof(uint32_t), 0)) == -1) {
      perror("recv(): ");
      return 1;
    }
    count += n;
  }
  printf("Received %d bytes.\n", count);
  
  sum = 0;
  data = (uint32_t*) buffer;
  for (int i = 0; i < 4; i++) {
    sum += data[i];
  }
  printf("Sum of four uint32_t's read: %u.\n", sum);
  
  if (send(sockfd, &sum, sizeof(uint32_t), 0) == -1) {
    perror("send(): ");
    return 1;
  }
  
  if ((n = recv(sockfd, buffer, sizeof(buffer), 0)) == -1) {
    perror("recv(): ");
    return 1;
  }
  printf("Response from server: %s\n", buffer);

  close(sockfd);
  return 0;
}
