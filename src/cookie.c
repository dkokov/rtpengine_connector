#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "mem.h"
#include "cookie.h"

static int cookie_pattern_1;
static int cookie_pattern_2;
static int cookie_pattern_3;

int cookie_rand(void)
{
	srand(time(NULL));
	return rand() % COOKIE_MAX + 1;
}

void cookie_init(void)
{
	cookie_pattern_1 = cookie_rand();
	cookie_pattern_2 = cookie_rand();
	cookie_pattern_3 = 0;
}

char *cookie_generator(void)
{
	int len;
	char buf[COOKIE_BUFFER_LEN],*ptr;

	if(cookie_pattern_3 == COOKIE_MAX) {
		if(cookie_pattern_2 == COOKIE_MAX) {
			if(cookie_pattern_1 == COOKIE_MAX) {
				cookie_pattern_1 = cookie_rand();
			} else cookie_pattern_1++;
			cookie_pattern_2 = cookie_rand();
		} else cookie_pattern_2++;
		cookie_pattern_3 = 0;
	}

	cookie_pattern_3++;

	memset(buf,0,COOKIE_BUFFER_LEN);
	sprintf(buf,"%d_%d_%d",cookie_pattern_1,cookie_pattern_2,cookie_pattern_3);
	len = strlen(buf);

	ptr = mem_alloc(len);
	if(ptr != NULL) {
		strcpy(ptr,buf);
	}

	return ptr;
}
