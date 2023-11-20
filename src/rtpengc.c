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

char *rtpengc_sdp(char *sdp)
{
	return bencode_append_str(bencode_bstring("sdp"),bencode_bstring(sdp));
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

void rtpengc_offer(rtpengc_conf_t *cfg,char *sdp,char *call_id,char *ip_addr,char *from_tag)
{
/*
d3:sdp
393:v=0
o=- 1917940926 1917940926 IN IP4 190.239.16.180
s=Asterisk
c=IN IP4 190.239.16.180
t=0 0
m=audio 10530 RTP/AVP 0 8 18 9 97 2 3 101
a=rtpmap:0 PCMU/8000
a=rtpmap:8 PCMA/8000
a=rtpmap:18 G729/8000
a=rtpmap:9 G722/8000
a=rtpmap:97 iLBC/8000
a=rtpmap:2 G726-32/8000
a=rtpmap:3 GSM/8000
a=rtpmap:101 telephone-event/8000
a=fmtp:101 0-16
a=ptime:20
a=sendrecv
a=direction:both

9:direction
4:both

3:ICE
6:remove

7:replace
l6:origin18:session-connectione

18:transport-protocol7:RTP/AVP

8:rtcp-muxl5:demuxe

7:call-id36:5228ec66-5ae8-4022-82f4-2919becc1bf5

13:received-froml3:IP410:10.42.3.80e

8:from-tag36:45d28661-9d60-4c80-a846-795b0b9cbd71

7:command5:offer
e

*/
	char *tmp,*tmp2,*_sdp;
	char buf[RTPENGC_BUF_SIZE];
	char *cookie_ptr;

	cookie_ptr = cookie_generator();

	_sdp = rtpengc_sdp(sdp);
	tmp = bencode_append_str(_sdp,rtpengc_call_id(call_id));
	tmp2 = bencode_append_str(tmp,rtpengc_received_from(ip_addr));
	tmp = bencode_append_str(tmp2,rtpengc_from_tag(from_tag));
	tmp2 = bencode_append_str(tmp,rtpengc_command("offer"));
	tmp = bencode_dictionary(tmp2);

	memset(buf,0,RTPENGC_BUF_SIZE);
	sprintf(buf,"%s %s",cookie_ptr,tmp);

	rtpengc_send(cfg,buf);
	rtpengc_recv(cfg);

	mem_free(tmp);
	mem_free(cookie_ptr);
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
