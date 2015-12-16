#!/bin/make
#compiler options
CC  = clang
CFLAGS = -std=c99 -pedantic -Wall -Werror -DUSE_AVL -O0 -g3

#defining c-files for server
C_FILES_SERVER = server.c KVS.c

#Object files string substitution for suffixes
O_FILES_SERVER = $(C_FILES_SERVER:%.c=%.o)

#library configuration
LIBRARY = avl
LIBPATH = .

#putting together linking flags
LD_FLAGS = -L$(LIBPATH) -l$(LIBRARY)

.PHONY: all, clean

#begin of main target
all: server

#begin of implied rules for compiling object files
%.o:%.c %.h myIPC.h
	$(CC) -c $(CFLAGS) $<

%.o:%.c myIPC.h
	$(CC) -c $(CFLAGS) $<

#begin of linking executables
server: $(O_FILES_SERVER)
	$(CC) -o $@ $(O_FILES_SERVER) $(CFLAGS) $(LD_FLAGS)

#clean target
clean:
	rm -rf *.o
	rm -rf server
