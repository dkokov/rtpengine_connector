#include "rtpengc.h"

void rtpengc_udp_init(rtpengc_conf_t *cfg)
{
	cfg->net_init = udp_init;
	cfg->net_send = udp_send;
	cfg->net_recv = udp_recv;
	cfg->net_conn = udp_conn;
	cfg->net_close = udp_close;
}

void rtpengc_tcp_init(rtpengc_conf_t *cfg)
{
	
}

rtpengc_conf_t *rtpengc_init(char *proto, char *ip,short port)
{
	rtpengc_conf_t *cfg;
	cfg = mem_alloc(sizeof(rtpengc_conf_t));

	if(cfg == NULL) return NULL;

	if(strcmp(proto,"udp") == 0) {
		cfg->t = udp;
		rtpengc_udp_init(cfg);
	} else if (strcmp(proto,"tcp") == 0) {
		cfg->t = tcp;
		rtpengc_tcp_init(cfg);
	} else cfg->t = 0;

	cfg->net_cfg = cfg->net_init(ip,port);

	return cfg;
}

int rtpengc_conn(rtpengc_conf_t *cfg)
{
	return cfg->net_conn(cfg->net_cfg);
}

void rtpengc_close(rtpengc_conf_t *cfg)
{
	cfg->net_close(cfg->net_cfg);
}

void rtpengc_send(rtpengc_conf_t *cfg,char *msg)
{
	cfg->net_send(cfg->net_cfg,msg);
}

void rtpengc_recv(rtpengc_conf_t *cfg)
{
	cfg->net_recv(cfg->net_cfg);
}

void rtpengc_ping(rtpengc_conf_t *cfg)
{
	rtpengc_send(cfg,"1234_5678_4 d7:command4:pinge");
	rtpengc_recv(cfg);
}

void rtpengc_offer()
{
	
}

void rtpengc_answer()
{
	
}
