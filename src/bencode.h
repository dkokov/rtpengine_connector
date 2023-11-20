#ifndef BENCODE_H
#define BENCODE_H

#define BENCODE_BUFFER_LEN 1024

typedef union bencode_content {
	char *bstring;
	int digit;
	char *list;
	char *dictonary;
} bencode_content_t;

typedef enum bencode_type {
	bstring=1,
	integer,
	list,
	dictionary
} bencode_type_t;

typedef struct bencode_node {
	//bencode_content_t content;
	char *content;
	bencode_type_t type;
	struct bencode_node *prev;
	struct bencode_node *next;
} bencode_node_t;

bencode_node_t *bencode_node_init();
char *bencode_bstring(char *src);
char *bencode_integer(int dig);
void bencode_free(bencode_node_t *lst);
char *bencode_append_str(char *curr,char *src);
char *bencode_list(char *content);
char *bencode_dictionary(char *content);

#endif
