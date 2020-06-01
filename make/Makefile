CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=hellobin

all: $(EXEC)

hellobin: function.o hello.o
	$(CC) -o hellobin function.o hello.o $(LDFLAGS)

function.o: function.c
	$(CC) -o function.o -c function.c $(CFLAGS)

hello.o: hello.c function.h
	$(CC) -o hello.o -c hello.c $(CFLAGS)

clean:
	rm -rf *.o

cleanall: clean
	rm -rf $(EXEC)

