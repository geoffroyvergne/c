# intel asm

## macho64

rm -Rf ./bin/hello_macho* && \
nasm -f macho64 hello_macho64.asm -o bin/hello_macho64.o && \
ld -no_pie -lSystem -o bin/hello_macho64 bin/hello_macho64.o && \
./bin/hello_macho64

## elf64

rm -Rf ./bin/hello_elf* && \
nasm -f elf64 hello_elf64.asm -o bin/hello_elf64.o && \
ld -o bin/hello_elf64 bin/hello_elf64.o && \
./bin/hello_elf64

