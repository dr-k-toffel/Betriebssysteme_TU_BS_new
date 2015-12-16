CFLAGS = -std=c99 -pedantic -D_BSD_SOURCE -Wall -Werror
CC=clang
.PHONY: all clean

all: loli

loli: main.c loli.c
	$(CC) $(CFLAGS) -o loli loli.c main.c

clean:
	rm -f loli
