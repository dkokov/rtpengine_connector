#include "udp.h"

void *udp_init(char *ip,short port)
{
	udp_conf_t *cfg = (udp_conf_t *) mem_alloc(sizeof(udp_conf_t));

	if (cfg == NULL) return NULL;

	strcpy(cfg->udp_server_ip,ip);
	cfg->udp_server_port = port;

	return (void *)cfg;
}

int udp_conn(void *_cfg)
{
	udp_conf_t *cfg = (udp_conf_t *) _cfg;
    cfg->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (cfg->sockfd < 0) {
        return -1;
    }

    memset(&cfg->server_addr, 0, sizeof(cfg->server_addr));

    cfg->server_addr.sin_family = AF_INET;
    cfg->server_addr.sin_port = htons(cfg->udp_server_port);
    inet_pton(AF_INET, cfg->udp_server_ip, &cfg->server_addr.sin_addr);
	cfg->addr_len = sizeof(cfg->server_addr);

	return 0;
}

int udp_send(void *_cfg,char *msg)
{
	udp_conf_t *cfg = (udp_conf_t *) _cfg;
    int msg_len = strlen(msg);

    sendto(cfg->sockfd, msg, msg_len, 0, (struct sockaddr *)&cfg->server_addr, sizeof(cfg->server_addr));

	return 0;
}

int udp_recv(void *_cfg)
{
	udp_conf_t *cfg = (udp_conf_t *) _cfg;
    cfg->recv_buf_ptr->rcv_buf_len = recvfrom(cfg->sockfd, cfg->recv_buf_ptr->rcv_buf, UDP_RECV_BUF, 0, (struct sockaddr *)&cfg->server_addr, &cfg->addr_len);	
        if (cfg->recv_buf_ptr->rcv_buf_len < 0) {
        //perror("Error in recvfrom");
    } else {
        cfg->recv_buf_ptr->rcv_buf[cfg->recv_buf_ptr->rcv_buf_len] = '\0';
        printf("Received: %s\n", cfg->recv_buf_ptr->rcv_buf);
    }
}

void udp_close(void *_cfg)
{
	udp_conf_t *cfg = (udp_conf_t *) _cfg;
	close(cfg->sockfd);
}
