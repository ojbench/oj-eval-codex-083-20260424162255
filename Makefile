CC=gcc
CFLAGS=-O2 -std=c11 -Wall -Wextra -Werror -pedantic
LDFLAGS=

all: code

code: main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f code *.o

.PHONY: all clean
