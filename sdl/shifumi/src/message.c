#include <stdio.h>
#include <message.h>

void message_init(struct Message *message, SDL_Renderer *render) {
    message->render = render;

    SDL_Color color = { 128, 128, 128 };
    SDL_Rect textureParams = { 128, 30,  256, 45 };
   
    message->fontPath = "../assets/arial.ttf";
    message->message = "shifumi";
    message->color = color;
    message->textureParams = textureParams;
    message->fontSize = 40;

    TTF_Init();
    message->font = TTF_OpenFont(message->fontPath, message->fontSize);
}

void message_displayMessage(struct Message *message) {
    message->sdlSurface = TTF_RenderText_Blended(message->font, message->message, message->color);
    message->sdlTexture = SDL_CreateTextureFromSurface(message->render, message->sdlSurface);
    SDL_RenderCopy(message->render, message->sdlTexture, NULL, &message->textureParams);  

    //SDL_DestroyTexture(message->sdlTexture);
    //SDL_FreeSurface(message->sdlSurface);
}

void message_cleanUp(struct Message *message) {
    TTF_CloseFont(message->font);    
    TTF_Quit();
}
