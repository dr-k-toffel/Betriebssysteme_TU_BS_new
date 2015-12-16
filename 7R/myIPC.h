#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DEF_IP "127.0.0.1"
#define DEF_PORT 424242

#define MAXSOCKETQUEUE 20

