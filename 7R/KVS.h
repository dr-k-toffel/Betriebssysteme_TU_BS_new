#ifndef __KVS_H__
#define __KVS_H__
int init_connection(void);
int accept_connection(int accept_socket);
int handle_connection(int accepted_socket);
int test_wrappers(void);
void clean_up_tree(void);
#endif
