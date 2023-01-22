#include <stdio.h>
#include <game.h>
//#include <message.h>
#include <core.h>

void game_renderView() {
    SDL_RenderClear(core->render);

    SDL_Rect textureParamsTitle = { 128, 20,  256, 35 };
    SDL_Color colorTitle = { 255, 165, 0 };
    core_display_message("Shifumi", colorTitle, 40, textureParamsTitle);

    SDL_Rect textureParamsScore = { 120, 55,  260, 60 };
    SDL_Color colorScore = { 128, 128, 128 };
    core_display_message(game_getScore(), colorScore, 20, textureParamsScore);

    piece_display(game->player1->piece);
    piece_display(game->player2->piece);

    SDL_RenderPresent(core->render);
}

void game_startLoop() {
    int active = 1;
    SDL_Event e;
    while (active) {
        
        while (SDL_PollEvent(&e)) {	            

            //if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
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

                        SDL_Delay(core->loopDelay);

                        game_result();
                        game_setWinner(game->winner);

                        SDL_Log("player1 : %s player2 : %s", game->player1->piece->name, game->player2->piece->name);              
                        SDL_Log("partyNumber %d winner : %s", game->partyNumber, game_getWinner(game->winner)->name);                       
                        SDL_Log("%s" , game_getScore());

                        game_newGame();

                        game_renderView();

                        break;
                    }

                    if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN) {
                        //SDL_Log("change piece");

                        piece_nextPiece(game->player1->piece);
                        
                        break;
                    }

                    // reset key
                    if (e.key.keysym.sym == SDLK_r) {
                        SDL_Log("New Game\n");
                        game->partyNumber = 0;
                        game->player1->score = 0;
                        game->player2->score = 0;
                    }
                    break;
                }
        }
        //SDL_Delay(core->loopDelay); 
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
    sprintf(result, "%d %s - %d | %s - %d", 
        game->partyNumber, game->player1->name, game->player1->score, game->player2->name, game->player2->score);

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
