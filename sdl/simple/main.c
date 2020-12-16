#include <SDL.h>
#include <stdio.h>

SDL_Surface *demo_screen;

int main(int argc, char** argv) {
    SDL_Event ev;
    int active;

    // Init SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
    }

    printf("SDL Initialized\n");

    demo_screen = SDL_SetVideoMode(320, 240, 0, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if(!demo_screen) {
        fprintf(stderr, "Could not set video mode: %s\n", SDL_GetError());
    }

    // Main loop
    active = 1;
    while(active) {
        while(SDL_PollEvent(&ev)) {

            // Handle event
            if(ev.type == SDL_QUIT) {
                active = 0;
                printf("Quit\n");
            }

            // Clear screen
            //SDL_FillRect(demo_screen,NULL,SDL_MapRGBA(demo_screen->format,0,0,255,255));

            // Show screen
            SDL_Flip(demo_screen);

        }
    }

    SDL_Quit();
    printf("SDL Shutdown\n");

    return 0;
}
