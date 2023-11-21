#include "../rtpengc.h"

#define UDP_SERVER_DEFAULT "127.0.0.1"
#define UDP_PORT_DEFAULT 2223

#define TEST_CALL_ID "1234567890abcdef-1234567890-1234567890abcdef-1234567890"
#define TEST_IP_ADDR "123.123.123.124"
#define TEST_FROM_TAG "b1ca3a4b1abcd"
#define TEST_SDP "v=0\r\no=- 1917940926 1917940926 IN IP4 190.239.16.180\r\ns=Asterisk\r\nc=IN IP4 190.239.16.180\r\nt=0 0\r\nm=audio 10530 RTP/AVP 0 8 18 9 97 2 3 101\r\na=rtpmap:0 PCMU/8000\r\na=rtpmap:8 PCMA/8000\r\na=rtpmap:18 G729/8000\r\na=rtpmap:9 G722/8000\r\na=rtpmap:97 iLBC/8000\r\na=rtpmap:2 G726-32/8000\r\na=rtpmap:3 GSM/8000\r\na=rtpmap:101 telephone-event/8000\r\na=fmtp:101 0-16\r\na=ptime:20\r\na=sendrecv\r\na=direction:both\r\n"


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
				rtpengc_offer(cfg,TEST_SDP,TEST_CALL_ID,TEST_IP_ADDR,TEST_FROM_TAG);
				break;
			case answer:
				break;
			case delete:
				rtpengc_delete(cfg,TEST_CALL_ID,TEST_IP_ADDR,TEST_FROM_TAG);
				break;
		};

		rtpengc_close(cfg);
		rtpengc_free(cfg);
	}

	return 0;
}
