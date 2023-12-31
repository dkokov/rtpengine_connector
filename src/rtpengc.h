#ifndef RTPENGC_H
#define RTPENGC_H

#include "udp.h"
#include "cookie.h"
#include "bencode.h"

#define RTPENGC_BUF_SIZE 2048

typedef enum net_proto {
	udp=1,
	tcp
} net_proto_t;


typedef void *(*net_init_func)(char *, short);
typedef int (*net_conn_func)(void *);
typedef void (*net_close_func)(void *);
typedef int (*net_send_func)(void *,char *);
typedef int (*net_recv_func)(void *);
typedef void (*net_free_func)(void *);

typedef struct rtpengc_conf {
	net_proto_t t;
	void *net_cfg;
	net_init_func net_init;
	net_conn_func net_conn;
	net_close_func net_close;
	net_send_func net_send;
	net_recv_func net_recv;
	net_free_func net_free;
} rtpengc_conf_t;

rtpengc_conf_t *rtpengc_init(char *proto, char *ip,short port);
void rtpengc_free(rtpengc_conf_t *cfg);
int rtpengc_conn(rtpengc_conf_t *cfg);
void rtpengc_close(rtpengc_conf_t *cfg);
void rtpengc_ping(rtpengc_conf_t *cfg);
void rtpengc_delete(rtpengc_conf_t *cfg,char *call_id,char *ip_addr,char *from_tag);
void rtpengc_offer(rtpengc_conf_t *cfg,char *sdp,char *call_id,char *ip_addr,char *from_tag);

#endif
