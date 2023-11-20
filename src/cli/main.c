#include "../rtpengc.h"

#define UDP_SERVER_DEFAULT "127.0.0.1"
#define UDP_PORT_DEFAULT 2223

int main(int argc, char *argv[])
{
	int ret;
	char ip[16];
	short port = UDP_PORT_DEFAULT;

	if(argc < 2) {
		strcpy(ip,UDP_SERVER_DEFAULT); 
	} else if (argc < 3) {
		strcpy(ip,argv[1]);
	} else {
		strcpy(ip,argv[1]);
		port = (short)atoi(argv[2]);
	}

	printf("Connecting to %s:%d\n",ip,port);

	rtpengc_conf_t *cfg = rtpengc_init("udp",ip,port);

	if(cfg != NULL) {
	    //ret = rtpengc_conn(cfg);
	    if(ret == -1) {
			/* Error */
			printf("/nERROR/n");
			//return -1;
	    }

	    //rtpengc_ping(cfg);
	    rtpengc_delete("1234","10.0.0.1","1234567asdfg");
	    //rtpengc_close(cfg);
	}

	return 0;
}
