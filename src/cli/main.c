#include "../rtpengc.h"

int main(void)
{
	int ret;

	rtpengc_conf_t *cfg = rtpengc_init("udp","127.0.0.1",2222);

	ret = rtpengc_conn(cfg);
	if(ret == -1) {
		/* Error */
		printf("/nERROR/n");
	}

	rtpengc_ping(cfg);

	rtpengc_close(cfg);

	return 0;
}
