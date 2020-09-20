# GNU Make

## Generate Makefile
gcc -MM main.c
hello.o: hello.c function.h

make && make run