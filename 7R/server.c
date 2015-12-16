#include "KVS.h"
#include <string.h>
#include <stdio.h>

int main (int argc, char ** argv){
	printf("argv[1] %s\n" , argv[1]);
	if( (argc > 1) && strcmp(argv[1], "-tavl") == 0){
		//testing wrappers!
		printf("\ttesting wrappers!\n");
		test_wrappers();
		goto clean_up;
	}

	int closed = 1;
	//Declaration of some variables used for the connection
	int accept_socket = init_connection();
	if(accept_socket > 0){
		printf("\tConnection has been initialized succesfully\n");
	}
	else{
		goto clean_up;
	}

	int accepted_socket;
	closed = 1;
	while (1){
		if(closed){
			//Accepting a socket
			accepted_socket =  accept_connection(accept_socket);

			//check if socket is valid
			if(accepted_socket <= 0){
				printf("\t Error: Socket not valid, aborting\n");
				goto clean_up;
			}
			// print out a small message to indicate that a connection has been established
			printf("\tNew connection accepted\n");
			//marking connection as open
			closed = 0;
		}
		else{
			closed = handle_connection(accepted_socket);
			//if connection has been closed, print out a small message
			if(closed){
				printf("\tConnection has been closed -> Waiting for new connections\n");
			}
		}
	}

clean_up:
		printf("cleaning up tree\n");
		clean_up_tree();
}
