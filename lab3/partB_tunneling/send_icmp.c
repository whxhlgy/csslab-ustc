#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>



#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include<arpa/inet.h>

#include "send_icmp.h"

extern unsigned char sendbuff[BUFFSIZE];
extern unsigned char recvbuff[BUFFSIZE];

extern tunnel *tnel;
extern int sock;
extern struct sockaddr_in dest_addr;
extern unsigned short total_len;

static unsigned short icmp_checksum(
                unsigned short *ptr, int nbytes) {
    long sum;
    unsigned short oddbyte;
    unsigned short answer;
    sum = 0;
    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }
    if (nbytes == 1) {
        oddbyte = 0;
        *((uint8_t *) &oddbyte) = *(uint8_t *)ptr;
        sum += oddbyte;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;
    return answer;
}


void init_icmp_packet(const char *myname,
                     const char *whoname, const char *dst_ip) {
    tnel = (tunnel *)malloc(sizeof(tunnel));
    memcpy(tnel->sname, myname, strlen(myname));
    memcpy(tnel->dname, whoname, strlen(whoname));
    struct icmphdr *icmph = (struct icmphdr *)(sendbuff);

    icmph->code = 0;
    icmph->un.echo.id = htons(1);
    icmph->un.echo.sequence = htons(1);
    dest_addr.sin_family = AF_INET;
    inet_pton(AF_INET, dst_ip, &dest_addr.sin_addr);
}

int senddata(char *data) {
    struct icmphdr *icmph = (struct icmphdr *)(sendbuff);
    tunnel *send_tunnel = (tunnel *)(sendbuff + sizeof(struct icmphdr));

    // 设置 ICMP 包头部
    icmph->type = ICMP_ECHO;
    icmph->code = 0;
    icmph->un.echo.id = htons(1);
    icmph->un.echo.sequence = htons(1);

    // 将数据拷贝到 send_tunnel->data
    strncpy(send_tunnel->data, data, sizeof(tnel->data));

    // 设置 send_tunnel 的源和目标名称信息
    strncpy(send_tunnel->sname, tnel->sname, sizeof(send_tunnel->sname));
    strncpy(send_tunnel->dname, tnel->dname, sizeof(send_tunnel->dname));

    // 计算 ICMP 校验和
    icmph->checksum = icmp_checksum((unsigned short *)icmph, sizeof(struct icmphdr) + sizeof(tunnel));

    // 发送 ICMP 包
    if (sendto(sock, sendbuff, sizeof(struct icmphdr) + sizeof(tunnel), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) == -1) {
        perror("sendto");
        return -1;
    }
    return 0;
}

int filter(struct icmphdr *icmph){
    tunnel *recv = (tunnel *)(recvbuff + sizeof(struct iphdr)
                                      + sizeof(struct icmphdr)); 
    if (icmph->type != ICMP_ECHO ||
        (strcmp(recv->dname, tnel->sname) != 0))
        return 0;
    return 1;
}

void encrypt(){
}

void decrypt(){
}