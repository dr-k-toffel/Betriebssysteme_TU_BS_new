#include "myIPC.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include "avl.h"
//#include "backtrace.h"
//------------------------------------------------------------//
// write your AVL wrapper's here:
static struct avl_node_t * root = NULL;
//------------------------------------------------------------//
static uint32_t * get_value_by_key(uint32_t key){
	if (!root) 
	{
		//printf("root was NULL");
		return NULL;
	} 
	else
	{
		return (uint32_t *) avl_get_data(root, key);
	}
}
//------------------------------------------------------------//
static int set_value(uint32_t key, uint32_t value){ 
	
	uint32_t * tmp = get_value_by_key(key); // testen ob key existiert
	if (tmp) 
	{
		*tmp = value; // wenn ja ueberschreibe wert
	}
	else
	{
		uint32_t * memory = malloc(sizeof(uint32_t)); // hole speicher
		if (memory)
		{	
			*memory = value; // schreibe wert in den speicher
			root = avl_put_data(root, key, memory);	 // speichere im baum
		} 
		else 
		{
			return -1;
		}
	}
	return 0;
}
//------------------------------------------------------------//
static void cleanup(void * data, void * args){
	if (data) 
	{
		//printf("clean %i; ", *((uint32_t*) data));
		free(data);
	}
}
//------------------------------------------------------------//
void clean_up_tree(void){
	if (root) 
	{
		clean_up_avl(root, cleanup, NULL);
		root = NULL;
	}
}
//------------------------------------------------------------//
static void print_data(void * data, void * args){
	if (data) 
	{
		printf("%i; ", *((uint32_t*) data));
	}
}
//------------------------------------------------------------//
//------------------------------------------------------------//
// Begin of IPC functions
//------------------------------------------------------------//
//------------------------------------------------------------//
int init_connection(void){
// socket erstellt
	struct sockaddr_in* addr_listen;
	int addr_listen_size;
	int sock;
    
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) 
    {
       	printf(" Error opening socket\n");
		exit(-1);
	}

	addr_listen_size = sizeof(struct sockaddr_in);

	addr_listen = malloc(addr_listen_size);

    if (!addr_listen) 
    {
    	printf("Error no memory\n");
    	exit(-1);
    }
    
    memset(addr_listen, 0, sizeof(struct sockaddr_in));
    addr_listen->sin_family = AF_INET;
    addr_listen->sin_addr.s_addr = inet_addr(DEF_IP);
	addr_listen->sin_port = htons((uint16_t)DEF_PORT);
	
	if (bind(sock, (struct sockaddr *) addr_listen, addr_listen_size) < 0) 
	{
       	printf("Error binding socket\n");
		exit(-1);
	}

	if (listen(sock, MAXSOCKETQUEUE) < 0) 
	{
		printf("Error listen socket\n");
		exit(-1);
	}
	return sock;
}
//------------------------------------------------------------//
int accept_connection(int accept_socket){
	struct sockaddr_in addr_client;
	int addr_client_size;
	int conn;

	addr_client_size = sizeof(addr_client_size);
	conn = accept(accept_socket, (struct sockaddr *) &addr_client, (socklen_t*) &addr_client_size);
	
    if (conn < 0) 
    {
        perror("ERROR on accept");
        exit(1);
    }
	return conn;
}
//------------------------------------------------------------//
int handle_connection(int accepted_socket){
	int n;
	int size = 2048;
    char buffer[size];
	char delimiter[] = ":";

    bzero(buffer, size);


    if ((n = read(accepted_socket, buffer, size)) > 0)
	{
		char data[3][n];
		char *ptr;

		char ret[2048];
		
		//printf("Here is the message: %s\n", buffer);	

		for (int i = 0; i < 3; i++)
		{	
			bzero(data[i], n);
		}

		ptr = strtok(buffer, delimiter);
		int j = 0;
		
		while(ptr != NULL && j < 3) {
			//printf("next: %s\n", ptr);
			strcpy(data[j], ptr);
		 	ptr = strtok(NULL, delimiter);
		 	j++;
		}

		//printf("sertzeiruiutz %s sdyfhjgkhjhl\n", buffer);

		if (strstr(buffer, "r")) 
		{
			//printf("get\n");
			uint32_t key = atoi(data[1]);

			uint32_t* value = get_value_by_key(key);

			if(value) 
			{
				sprintf(ret, "a:%i:%i:", key, *value);
			}
			else
			{
				sprintf(ret, "d:%i:", key);	
			}

    		if (write(accepted_socket, ret , strlen(ret)) < 0) 
    		{
        		perror("ERROR writing to socket");
        		exit(1);
    		}
		} 
		else if (strstr(buffer, "s")) 
		{
			//printf("set\n");
			uint32_t key = atoi(data[1]);

			uint32_t value = atoi(data[2]);

			if(set_value(key, value) == 0) 
			{
				sprintf(ret, "a:%i:%i:", key, value);
			}
			else
			{
				sprintf(ret, "d:%i:", key);	
			}

    		if (write(accepted_socket, ret , strlen(ret)) < 0) 
    		{
        		perror("ERROR writing to socket");
        		exit(1);
    		}
		}
		else 
		{
			//printf("bla\n");
			if (write(accepted_socket, buffer , strlen(buffer)) < 0) 
    		{
        		perror("ERROR writing to socket");
        		exit(1);
    		}
		}

		return 0;
	} 
	else 
	{
		if (close(accepted_socket) < 0) // wenn nichts gelesen dann immer den socket schliessen
	    {
	    	perror("ERROR closing socket");
	        exit(1);	
	    }	
	}

    if (n < 0) // fehler
    {
        perror("ERROR reading from socket");
        exit(1);
    }

    return 1;
}
//------------------------------------------------------------//
//------------------------------------------------------------//
// do not edit following lines, it is not necessary to do so.
//------------------------------------------------------------//
//------------------------------------------------------------//
#define TEST_VALUES 10
// This function is used to test all avl wrapper's.
// If everything works fine, this function returns 0
// otherwise -1.
int test_wrappers(void){
	//initialize_signal_handler();
	set_value(255,255);
	preorder_work(root, print_data, NULL);
	printf("\n");

	set_value(255, 256);
	set_value(900, 900);
	preorder_work(root, print_data, NULL);
	printf("\n");

	for(uint32_t i = 0; i < TEST_VALUES; ++i){
		set_value(i, TEST_VALUES-i);
	}
	preorder_work(root, print_data, NULL);
	printf("\n");

	for(uint32_t i = 0; i < TEST_VALUES; ++i){
		if(*get_value_by_key(i) != TEST_VALUES-i){
			printf("ERROR: key-value pair does not match!\n");
			return -1;
		}
		printf("Key value pair: O.K.\n");
	}
	//testing double clean up calls
	printf("testing clean up tree\n");
	clean_up_tree();
	printf("done\n");
	printf("testing repeated cleanup... \n");
	//repeated clean up call is done by main function
	return 0;
}
