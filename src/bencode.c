/*
 * https://en.wikipedia.org/wiki/Bencode
 * 
 * */

#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "mem.h"
#include "bencode.h"

bencode_node_t *bencode_node_init()
{
	return mem_alloc(sizeof(bencode_node_t));
}

char *bencode_bstring(char *src)
{
	int len;
	char buf[BENCODE_BUFFER_LEN],*ptr;
	
	len = strlen(src);
	memset(buf,0,BENCODE_BUFFER_LEN);
	sprintf(buf,"%d:%s",len,src);
	len = strlen(buf);

	ptr = mem_alloc(len+1);
	if(ptr != NULL) {
		strcpy(ptr,buf);
	}

	return ptr;
}

char *bencode_integer(int dig)
{
	int len;
	char buf[BENCODE_BUFFER_LEN],*ptr;

	memset(buf,0,BENCODE_BUFFER_LEN);
	sprintf(buf,"i%de",dig);
	len = strlen(buf);

	ptr = mem_alloc(len+1);
	if(ptr != NULL) {
		strcpy(ptr,buf);
	}

	return ptr;
}

char *bencode_list(char *content)
{
	int len;
	char buf[BENCODE_BUFFER_LEN],*ptr;

	if(content == NULL) return NULL;

	memset(buf,0,BENCODE_BUFFER_LEN);
	sprintf(buf,"l%se",content);
	len = strlen(buf);

	ptr = mem_alloc(len+1);
	if(ptr != NULL) {
		strcpy(ptr,buf);
	}

	mem_free(content);

	return ptr;
}

char *bencode_dictionary(char *content)
{
	int len;
	char buf[BENCODE_BUFFER_LEN],*ptr;

	if(content == NULL) return NULL;
	
	memset(buf,0,BENCODE_BUFFER_LEN);
	sprintf(buf,"d%se",content);
	len = strlen(buf);

	ptr = mem_alloc(len+1);
	if(ptr != NULL) {
		strcpy(ptr,buf);
	}

	mem_free(content);

	return ptr;
}

int bencode_node_append(bencode_node_t *lst,char *ptr,bencode_type_t t)
{
	if(lst != NULL) {
		_top:
		if(lst->next != NULL) {
			lst = lst->next;
			goto _top;
		} else {
			lst->content = ptr;
			lst->type = t;
			lst->next = bencode_node_init();
		}
	}

	return 0;
}

char *bencode_node_to_str(bencode_node_t *lst)
{
	int len;
	char *ptr;
	char buf[BENCODE_BUFFER_LEN];
	char tmp[BENCODE_BUFFER_LEN];
	bencode_node_t *curr = lst;

	_top:
	if(curr != NULL) {
		memset(tmp,0,BENCODE_BUFFER_LEN);
		memcpy(tmp,buf,sizeof(buf));
		memset(buf,0,BENCODE_BUFFER_LEN);
		sprintf(buf,"%s%s",tmp,curr->content);
		curr = curr->next;
		goto _top;
	}

	len = strlen(buf);

	ptr = mem_alloc(len);
	if(ptr != NULL) {
		strcpy(ptr,buf);
	}

	return ptr;
}

char *bencode_append_str(char *curr,char *src)
{
	int len;
	char *ptr;
	char buf[BENCODE_BUFFER_LEN];

	if((curr != NULL)&&(src != NULL)) {
		memset(buf,0,BENCODE_BUFFER_LEN);
		sprintf(buf,"%s%s",curr,src);
	}

	len = strlen(buf);

	ptr = mem_alloc(len+1);
	if(ptr != NULL) {
		strcpy(ptr,buf);
	}

	mem_free(src);
	mem_free(curr);

	return ptr;
}

void bencode_free(bencode_node_t *lst)
{
	bencode_node_t *curr;

	_top:
	if(lst != NULL) {
		if(lst->content != NULL) { 
			mem_free(lst->content);
			lst->content = NULL;
		}
		curr = lst;
		lst = lst->next;
		mem_free(curr);
		goto _top;
	}
	lst = NULL;
}

