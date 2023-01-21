#include <stdio.h>
#include <core.h>

void core_init() {
    SDL_Log("core init");

    //Start up SDL, and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s\n", SDL_GetError());
        
		exit(EXIT_FAILURE);
	}

	// Create window
	core->window = SDL_CreateWindow(core->name, 100, 100, core->width, core->height, SDL_WINDOW_SHOWN);
	if (core->window == NULL) {core_cleanup(); exit(EXIT_FAILURE);}

	// Create render
	core->render = SDL_CreateRenderer(core->window, -1, 0);
	//render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	
	if (core->render == NULL) {core_cleanup(); exit(EXIT_FAILURE);}

    SDL_SetRenderDrawColor(core->render, 255, 255, 255, 255);
    //SDL_RenderClear(game_render);
	//SDL_RenderPresent(game_render); 

    core->sdl_texture = IMG_LoadTexture(core->render, "../assets/images-set.png");

    if(core->sdl_texture == NULL) {
        SDL_Log("sdl_texture NULL");
    }

    //SDL_Color color = { 128, 128, 128 };
    //SDL_Rect textureParams = { 128, 30,  256, 45 };

    core->fontPath = "../assets/arial.ttf";
    //core->message = "shifumi";
    //core->color = color;
    //core->textureParams = textureParams;
    //core->fontSize = 40;

    // init TTF messages
    TTF_Init();
    
}

void core_display_message(char* message, SDL_Color color, int fontSize, SDL_Rect textureParams) {
    core->font = TTF_OpenFont(core->fontPath, fontSize);
    core->sdlSurface = TTF_RenderText_Blended(core->font, message, color);
    core->message_sdl_texture = SDL_CreateTextureFromSurface(core->render, core->sdlSurface);
    SDL_RenderCopy(core->render, core->message_sdl_texture, NULL, &textureParams);  

    //SDL_DestroyTexture(core->sdl_texture);
    //SDL_FreeSurface(core->sdlSurface);
}

void core_cleanup() {
    SDL_DestroyRenderer(core->render);
    SDL_DestroyWindow(core->window);
	SDL_Quit();
}
