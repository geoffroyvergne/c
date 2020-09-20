CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=hellobin

all: $(EXEC)

hellobin: function.o hello.o
	$(CC) -o bin/hellobin bin/function.o bin/hello.o $(LDFLAGS)

function.o: function.c
	$(CC) -o bin/function.o -c function.c $(CFLAGS)

hello.o: hello.c function.h
	$(CC) -o bin/hello.o -c hello.c $(CFLAGS)

cleano:
	rm -rf bin/*.o

clean: cleano
	rm -rf bin/$(EXEC)

run:
	./bin/hellobin