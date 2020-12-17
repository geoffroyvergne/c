#include <stdio.h>
#include <SDL.h>

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* pWindow = NULL;
    pWindow = SDL_CreateWindow("SDL_CreateWindow Error", SDL_WINDOWPOS_UNDEFINED,
                                                        SDL_WINDOWPOS_UNDEFINED,
                                                        640,
                                                        480,
                                                        SDL_WINDOW_SHOWN);

    if( pWindow ) {
        //SDL_Delay(3000);

        int active = 1;
        SDL_Event e;                      
        while (active) {            
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    active = 0;
                }
            }
        }
        SDL_DestroyWindow(pWindow);
    }
    else {
        fprintf(stderr,"SDL_CreateWindow Error: %s\n",SDL_GetError());
    }

    SDL_Quit();

    return 0;
}
