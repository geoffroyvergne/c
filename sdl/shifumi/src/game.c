#include <stdio.h>
#include <game.h>
#include <message.h>

void game_init() {
    //Start up SDL, and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s\n", SDL_GetError());
        
		exit(EXIT_FAILURE);
	}

	// Create window
	game->window = SDL_CreateWindow(game->name, 100, 100, game->width, game->height, SDL_WINDOW_SHOWN);
	if (game->window == NULL) {game_cleanup(); exit(EXIT_FAILURE);}

	// Create render
	game->render = SDL_CreateRenderer(game->window, -1, 0);
	//render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	
	if (game->render == NULL) {game_cleanup(); exit(EXIT_FAILURE);}

    SDL_SetRenderDrawColor(game->render, 255, 255, 255, 255);
    //SDL_RenderClear(game_render);
	//SDL_RenderPresent(game_render); 
}

void game_renderView() {
    SDL_RenderClear(game->render);

    message_displayMessage(game->message);
    piece_display(game->player1->piece);
    piece_display(game->player2->piece);

    SDL_RenderPresent(game->render);
}

void game_startLoop() {
    int active = 1;
    SDL_Event e;
    while (active) {
        
        while (SDL_PollEvent(&e)) {	            

            //if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) {
            if (e.type == SDL_QUIT) {
				active = 0;
				SDL_Log("Quit");
			}            

            game_renderView();

            switch( e.type ) {
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE) {
                        if(game->player1->piece->pieceType == none) break;
                        
                        // Player 2 play random
                        piece_randomPiece(game->player2->piece);

                        // Update render
                        game_renderView();

                        SDL_Delay(1000);

                        game_result();
                        game_setWinner(game->winner);

                        SDL_Log("player1 : %s player2 : %s", game->player1->piece->name, game->player2->piece->name);              
                        SDL_Log("partyNumber %d winner : %s", game->partyNumber, game_getWinner(game->winner)->name);                       
                        SDL_Log("%s" , game_getScore());

                        // Update score message
                        game->message->message = game_getScore();
                        
                        game_newGame();

                        game_renderView();

                        //SDL_Delay(1000);

                        break;
                    }

                    if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN) {
                        //SDL_Log("change piece");

                        piece_nextPiece(game->player1->piece);
                        
                        break;
                    }
                    break;
                }
        }
        SDL_Delay(game->loopDelay); 
    }
}

void game_result() {
    if(game->player1->piece->pieceType == none && game->player2->piece->pieceType == none) game->winner = playerNoneType;

    else if(game->player1->piece->pieceType == rock && game->player2->piece->pieceType == rock) game->winner = playerNoneType;
    else if(game->player1->piece->pieceType == rock && game->player2->piece->pieceType == paper) game->winner = player2Type;
    else if(game->player1->piece->pieceType == rock && game->player2->piece->pieceType == sissors) game->winner = player1Type;

    else if(game->player1->piece->pieceType == paper && game->player2->piece->pieceType == rock) game->winner = player1Type;
    else if(game->player1->piece->pieceType == paper && game->player2->piece->pieceType == paper) game->winner = playerNoneType;
    else if(game->player1->piece->pieceType == paper && game->player2->piece->pieceType == sissors) game->winner = player2Type;

    else if(game->player1->piece->pieceType == sissors && game->player2->piece->pieceType == rock) game->winner = player2Type;
    else if(game->player1->piece->pieceType == sissors && game->player2->piece->pieceType == paper) game->winner = player1Type;
    else if(game->player1->piece->pieceType == sissors && game->player2->piece->pieceType == sissors) game->winner = playerNoneType;

    else game->winner = playerNoneType;
}

void game_setWinner(enum PlayerType type) {
    if(type == player1Type) {
        game->player1->winner = 1;
        game->player1->score ++;
    }

    else if(type == player2Type) {
        game->player2->winner = 1;
        game->player2->score ++;
    }
}

struct Player* game_getWinner(enum PlayerType type) {
    if(type == player1Type) return game->player1;
    if(type == player2Type) return game->player2;
    return game->playerNone;
}

char* game_getScore() {
    char *result = (char *) malloc( sizeof(char) * 2000 );
    sprintf(result, "%s - %d / %s - %d", 
        game->player1->name, game->player1->score, game->player2->name, game->player2->score);

    return result;
}

void game_newGame() {
    game->partyNumber ++;
    piece_togglePieceType(none, game->player1->piece);
    game->player1->winner = 0;

    piece_togglePieceType(none, game->player2->piece);
    game->player2->winner = 0;

    game->winner = playerNoneType;
}

void game_cleanup() {
    SDL_DestroyRenderer(game->render);
    SDL_DestroyWindow(game->window);
	SDL_Quit();
}
