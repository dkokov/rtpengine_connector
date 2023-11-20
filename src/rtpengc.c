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

	cookie_init();

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
	printf("debug send: %s\n",msg);
	cfg->net_send(cfg->net_cfg,msg);
}

void rtpengc_recv(rtpengc_conf_t *cfg)
{
	cfg->net_recv(cfg->net_cfg);
}

char *rtpengc_call_id(char *call_id)
{
	return bencode_append_str(bencode_bstring("call-id"),bencode_bstring(call_id));
}

char *rtpengc_command(char *command)
{
	return bencode_append_str(bencode_bstring("command"),bencode_bstring(command));
}

char *rtpengc_from_tag(char *from_tag)
{
	return bencode_append_str(bencode_bstring("from-tag"),bencode_bstring(from_tag));
}

char *rtpengc_received_from(char *ip_addr)
{
	char *tmp = bencode_append_str(bencode_bstring("IP4"),bencode_bstring(ip_addr));
	return bencode_append_str(bencode_bstring("received-from"),bencode_list(tmp));
}

void rtpengc_ping(rtpengc_conf_t *cfg)
{
	char *tmp;
	char buf[RTPENGC_BUF_SIZE];
	char *cookie_ptr;

	cookie_ptr = cookie_generator();

	tmp = bencode_dictionary(rtpengc_command("ping"));

	memset(buf,0,RTPENGC_BUF_SIZE);
	sprintf(buf,"%s %s",cookie_ptr,tmp);

	rtpengc_send(cfg,buf);
	rtpengc_recv(cfg);

	mem_free(tmp);
	mem_free(cookie_ptr);
}

void rtpengc_offer()
{
	
}

void rtpengc_answer()
{
	
}

void rtpengc_delete(rtpengc_conf_t *cfg,char *call_id,char *ip_addr,char *from_tag)
{
	char *tmp,*tmp2,*_call_id;
	char buf[RTPENGC_BUF_SIZE];
	char *cookie_ptr;

	cookie_ptr = cookie_generator();

	_call_id = rtpengc_call_id(call_id);
	tmp = bencode_append_str(_call_id,rtpengc_received_from(ip_addr));
	tmp2 = bencode_append_str(tmp,rtpengc_from_tag(from_tag));
	tmp = bencode_append_str(tmp2,rtpengc_command("delete"));
	tmp2 = bencode_dictionary(tmp);

	memset(buf,0,RTPENGC_BUF_SIZE);
	sprintf(buf,"%s %s",cookie_ptr,tmp2);

	rtpengc_send(cfg,buf);
	rtpengc_recv(cfg);

	mem_free(tmp2);
	mem_free(cookie_ptr);
}
