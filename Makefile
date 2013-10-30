# Makefile

CC=gcc
CFLAGS=-Wall -std=gnu99

LDFLAGS=-L ./

all : checklychrel

checklychrel: checklychrel.c liblychrel
	$(CC) -o checklychrel $(CFLAGS) checklychrel.c -L ./ -llychrel

liblychrel: lychrel.c
	$(CC) -o liblychrel.so -shared $(CFLAGS) lychrel.c

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY=clean

clean:
	rm checklychrel *.so

# eof