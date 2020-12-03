# Sanitizer

clang -o bin/use-after-free use-after-free.c -fsanitize=address -fno-omit-frame-pointer -Wall -Wextra

clang -o bin/use-after-free use-after-free.c -fno-omit-frame-pointer -Wall -Wextra

cmake . -B build/
cmake --build build/