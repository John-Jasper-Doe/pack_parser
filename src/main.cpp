#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#define SOCKET_ERROR -1
typedef int socktype_t;

static char buff[10 * 1014];

int main(/*int argc, const char* argv[]*/) {
  socktype_t my_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (my_sock == SOCKET_ERROR) {
    return 1;
  }

  //  struct sockaddr_in dest_addr;
  //  unsigned int dest_addr_size = sizeof(dest_addr);
  //  dest_addr.sin_family = AF_INET;
  //  inet_pton(AF_INET, (const char *) "127.0.0.1", &(dest_addr.sin_addr));
  //  dest_addr.sin_port = htons(9995);

  sockaddr_in local_addr;
  local_addr.sin_family = AF_INET;
  local_addr.sin_addr.s_addr = INADDR_ANY;
  local_addr.sin_port = htons(9995);

  if (bind(my_sock, (sockaddr*)&local_addr, sizeof(local_addr))) {
    return -1;
  }

  //  unsigned long count_09 = 0;
  //  unsigned long count_0a = 0;
  //  unsigned long count_all = 0;

  unsigned long traf_count[3] = {0, 0, 0};
  unsigned long traf_size[3] = {0, 0, 0};

  unsigned short size_data = 0;

  while (true) {  // D:\work\decoders.bak2\netflow_example.pcap.bin 00001.bin 10000.bin
    sockaddr_in server_addr;
    unsigned int server_addr_size = sizeof(server_addr);
    int n = recvfrom(my_sock, &buff[0], sizeof(buff) - 1, 0, (sockaddr*)&server_addr,
                     &server_addr_size);
    if (n == SOCKET_ERROR) {
      //      printf("recvfrom() error: %d\n",WSAGetLastError());
      return 1;
    }

    buff[n] = 0;

    if (buff[1] == 0x09) {
      ++traf_count[0];
      traf_size[0] += n;
    }
    else if (buff[1] == 0x0a) {
      ++traf_count[1];
      traf_size[1] += n;
    }
    else {
      ++traf_count[2];
      traf_size[2] += n;
    }

    ((unsigned char*)&size_data)[0] = buff[3];
    ((unsigned char*)&size_data)[1] = buff[2];

    printf("09: = %lu/%lu, 0a: = %lu/%lu, other: = %lu/%lu\n", traf_count[0], traf_size[0],
           traf_count[1], traf_size[1], traf_count[2], traf_size[2]);
  }

  return EXIT_SUCCESS;
}
