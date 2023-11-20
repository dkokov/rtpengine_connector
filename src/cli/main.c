#include "../rtpengc.h"

#define UDP_SERVER_DEFAULT "127.0.0.1"
#define UDP_PORT_DEFAULT 2223

typedef enum test_mode {
	ping=1,
	offer,
	answer,
	delete
} test_mode_t;

int main(int argc, char *argv[])
{
	int ret,mode;
	char ip[16];
	short port = UDP_PORT_DEFAULT;

	mode = ping;

	if(argc < 2) {
		strcpy(ip,UDP_SERVER_DEFAULT); 
	} else if (argc < 3) {
		strcpy(ip,argv[1]);
	} else {
		strcpy(ip,argv[1]);
		port = (short)atoi(argv[2]);

		if(strcmp(argv[3],"ping")==0){
			mode = ping;
		} else if(strcmp(argv[3],"offer")==0) {
			mode = offer;
		} else if(strcmp(argv[3],"answer")==0) {
			mode = answer;
		} else if(strcmp(argv[3],"delete")==0) {
			mode = delete;
		} else {
		}
	}

	printf("Connecting to %s:%d\n",ip,port);

	rtpengc_conf_t *cfg = rtpengc_init("udp",ip,port);

	if(cfg != NULL) {
	    ret = rtpengc_conn(cfg);
	    if(ret == -1) {
			/* Error */
			printf("/nERROR/n");
			return -1;
	    }

		switch(mode) {
			case ping:
				rtpengc_ping(cfg);
				break;
			case offer:
				break;
			case answer:
				break;
			case delete:
				rtpengc_delete("1234","10.0.0.1","1234567asdfg");
				break;
		};

		rtpengc_close(cfg);
	}

	return 0;
}
