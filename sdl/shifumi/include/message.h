#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>

#ifndef MESSAGE
#define MESSAGE

struct Message { 
    char* fontPath;
    SDL_Renderer *render;
    TTF_Font * font;
    int fontSize;
    char* message;
    SDL_Color color;
    SDL_Texture * sdlTexture;
    SDL_Surface * sdlSurface;
    SDL_Rect textureParams;
};

void message_init(struct Message *message, SDL_Renderer *render);
void message_displayMessage(struct Message *messag);
void message_cleanUp(struct Message *message);

#endif
