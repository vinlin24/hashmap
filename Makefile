CC = gcc
CFLAGS = -Wall -Wextra -g

default: main

.PHONY: clean

SOURCES = $(shell ls *.c)
OBJECTS = $(SOURCES:.c=.o)

%.o: %.c $(wildcard %.h)
	$(CC) $(CFLAGS) -c $^ -o $@

main: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o main
