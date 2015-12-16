CFLAGS = -std=c99 -g -O0 -pedantic -Wall
CC=gcc

.PHONY: all clean 

all: lili

lili: lili.c test.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm lili *.o


