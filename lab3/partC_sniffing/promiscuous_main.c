#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO()\
do{\
    extern int printf(char *, ...);\
    printf("Add your code here: file %s, line %d\n", __FILE__, __LINE__);\
}while(0)



// socket
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
// ETH_P_ALL
#include <net/ethernet.h>
// ioctl
#include <sys/ioctl.h>
// struct ifeq
#include <net/if.h>
#include "packet-analyze.h"

// if you set the default port to 80, then you are
// required to gain the root privilege to bind this port.
#define HOST_PORT 12345
#define DEBUG 1
#define BUF_SIZE 65536
#define MAX_ROUND 1000
static char buf[BUF_SIZE];

// create the socket (set up the required flag for mode):
int raw_init (const char *device){
    // Exercise 1: Create a raw socket and enable promiscuous mode
    // Add your code here:
    TODO();

}

// clear the flag:
void clear_flag(char *device, int sock_fd){
    // Exercise 1: turn off promiscuous mode
    // Add your code here:
    TODO();

}

int main (int argc, char **argv){
    int max_rounds = MAX_ROUND;
    if(argc < 2){
        printf("Usage: ./main.out <device>\n");
        exit(1);
    }
    char *device = argv[1];

    // create a new raw socket
    int sock_fd = raw_init(device);
    printf("Start sniffing\n");

    while(1){
        // the specification requires to initialize the sock_addr_len:
        struct sockaddr sock_addr;
        memset(&sock_addr, 0, sizeof(sock_addr));
        unsigned int sock_addr_len = sizeof(sock_addr);
        ssize_t n = recvfrom(sock_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&sock_addr, &sock_addr_len);
        if (n == -1)
            printf("Error: socket recv\n");

        // analyze the received packet:
        packet_analyze(buf, n);
    }
    // a summary:
    printf("arps = %d, ips = %d, ipv6 = %d\n",
           eth_count.arps, eth_count.ips, eth_count.ipv6s);
    printf("tcps = %d, udps = %d\n", ip_count.tcps, ip_count.udps);

    clear_flag(device, sock_fd);
    close(sock_fd);
    return 0;
}





