CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=http-server

all: clean build run

build:
	$(CC) -o bin/$(EXEC) $(EXEC).c $(LDFLAGS)

clean:
	rm -f bin/$(EXEC)

run:
	./bin/$(EXEC)