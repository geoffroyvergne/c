CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=hello-world

all: clean build run

build:
	$(CC) -o bin/$(EXEC) hello-world.c $(LDFLAGS)

clean:
	rm -f bin/$(EXEC)

run:
	./bin/$(EXEC)