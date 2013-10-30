# Build fails with mingw

CC=gcc
CFLAGS=-Wall -std=gnu99 -O3

all : lychrel

lychrel: lychrel.c
	$(CC) -o lychrel $(CFLAGS) lychrel.c

.PHONY=clean

clean:
	rm lychrel

# eof