#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 512
#define MAGIC 0xCAFE
#define PORT 6767

struct Packet
{
  uint16_t magic;
  uint64_t size;
  char body[];
} __attribute__((packed));

struct Packet *createPacket(char* body)
{
  uint64_t size = strlen(body);
  struct Packet *packet = malloc(10 + size);
  packet->magic = htons(MAGIC);
  packet->size = htobe64(size);
  for (int i = 0; i < size; i++)
  {
    packet->body[i] = body[i];
  }
  
  return packet;
}

struct Packet *sendPacket(struct Packet *packet)
{
  int sock, totalSize = sizeof(struct Packet) + packet->size;
  struct sockaddr_in serverAddress;
  char *buffer = malloc(BUFFER_SIZE);
  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
  
  if (connect(sock, (struct sockaddr *)&serverAddress, \
  sizeof(serverAddress)) < 0)
  {
    printf("Connection failed.\n");
    return NULL;
  }
  
  send(sock, packet, totalSize, 0);
  
  int readSize = read(sock, buffer, BUFFER_SIZE);
  close(sock);
  
  if (readSize > 0)
    return (struct Packet *)buffer;
  return NULL;
}


int main()
{
  struct Packet *test = createPacket("miau :3");
  struct Packet *response = sendPacket(test);
  if (response != NULL)
    printf("%s", response->body);
  
  free(test);
  return 0;
}
