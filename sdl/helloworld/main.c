#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

SDL_Window *win;
SDL_Renderer *ren;

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

void cleanup(int status) {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	if(status == 1) {
		exit(EXIT_FAILURE);
	}
}

void init() {
	//First we need to start up SDL, and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s\n", SDL_GetError());
        
		exit(EXIT_FAILURE);
	}
}

SDL_Surface* loadImage(char* file, SDL_Renderer *ren){
	SDL_Surface *img = IMG_Load(file);
    if (img == NULL){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
		return NULL;
	}

	return img;
}

SDL_Texture* renderSurface(SDL_Renderer *ren, SDL_Surface *img) {
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, img);
	//We no longer need the surface
	SDL_FreeSurface(img);
	if (tex == NULL){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", IMG_GetError());
		return NULL;
	}

	return tex;
}

SDL_Texture* loadTexture(char* file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file);
	if (texture == NULL){		
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "LoadTexture");
	}
	return texture;
}

int main(int argc, char** argv) {

	// Init SDL
    init();

	// Create window
	win = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL) cleanup(1);

	// Create render
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) cleanup(1);

	// Load background image
	SDL_Surface *img = loadImage("../nintendo-logo.jpg", ren);
	if (img == NULL) cleanup(1);

	SDL_Texture *tex = renderSurface(ren, img);
	if (tex == NULL) cleanup(1);

	// Start Loop
	int active = 1;
	SDL_Event e;
	while (active) {
		while (SDL_PollEvent(&e)) {
			SDL_RenderClear(ren);
			SDL_RenderCopy(ren, tex, NULL, NULL);
			SDL_RenderPresent(ren);
			
			if (e.type == SDL_QUIT) {
				active = 0;
				SDL_Log("Quit\n");
			}

			//SDL_Delay(1000);
		}
	}

	SDL_DestroyTexture(tex);
	cleanup(0);

	/*SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);*/

    return EXIT_SUCCESS;
}
