#include <stdio.h>
#include <SDL.h>

#include <SDL_image.h>
#include <SDL_ttf.h>

#ifndef CORE
#define CORE

struct Core {  
    char* name;
    int width;
    int height;
    int loopDelay;

    char* fontPath;
    //int fontSize;
    char* message;

    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Texture *sdl_texture;

    //SDL_Color color;
    SDL_Surface * sdlSurface;
    SDL_Texture * message_sdl_texture;

    TTF_Font * font;
};

struct Core *core;

void core_init();
void core_display_message(char* message, SDL_Color color, int fontSize, SDL_Rect textureParams);
void core_cleanup();

#endif
