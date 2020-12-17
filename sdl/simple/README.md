# V1 sdl lib

gcc main.c `sdl-config --cflags --libs` -o bin/sdltest

cmake -S . -B build/
cmake --build build/
