#ifndef UDP_H
#define UDP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "mem.h"

#define UDP_RECV_BUF 1024

typedef struct udp_recv_buf {
	unsigned int rcv_buf_len;
	char rcv_buf[UDP_RECV_BUF];
} udp_recv_buf_t;

typedef struct udp_conf {
	int sockfd;
	short udp_server_port;
	char udp_server_ip[16];
	socklen_t addr_len;
	struct sockaddr_in server_addr;
	udp_recv_buf_t *recv_buf_ptr;
} udp_conf_t;

void *udp_init(char *ip,short port);
int udp_conn(void *_cfg);
int udp_send(void *_cfg,char *msg);
int udp_recv(void *_cfg);
void udp_close(void *_cfg);
void udp_free(void *cfg);

#endif
