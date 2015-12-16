# NOTES
#--------
# parameters needed for kill(2):
# Compilation with _XOPEN_SOURCE 

# parameters needed for backtrace(3):
# Compilation with -fno-omit-frame-pointer 
# Linking with -rdynamic (gcc) or -Wl,--export-dynamic (clang)

CFLAGS=-std=c99 -g3 -O0 -pedantic -Wall -D_XOPEN_SOURCE=600 -fno-omit-frame-pointer

#CC=clang
#LDFLAGS=-Wl,--export-dynamic

# for clang under MAC:
# CC=clang
# LDFLAGS=-Wl,-export_dynamic

# for gcc
 CC=gcc
 LDFLAGS=-rdynamic 

EXECUTABLES=test signal

.PHONY: all clean

all: $(EXECUTABLES)

clean:
	rm -f *.o $(EXECUTABLES)

%.o: %.c %.h Makefile
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.c Makefile
	$(CC) $(CFLAGS) -o $@ -c $<

test: test.o backtrace.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

signal: signal.o backtrace.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

run: test
	./test
