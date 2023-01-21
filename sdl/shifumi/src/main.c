#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <core.h>
#include <game.h>
#include <player.h>
#include <piece.h>

int main(int argc, char** argv) {
    
    core = (struct Core*) malloc(sizeof(struct Core));
    core->name = "shifumi";
    core->width = 512;
    core->height = 512;
    core->loopDelay = 200;

    core_init();

    game = (struct Game*) malloc(sizeof(struct Game));
    game->partyNumber = 0;

    game->player1 = (struct Player*) malloc(sizeof(struct Player));
    game->player1->name = "player1";
    game->player1->score = 0;
    game->player1->type = player1Type;
    game->player1->winner = 0;
    
    game->player2 = (struct Player*) malloc(sizeof(struct Player));
    game->player2->name = "player2";
    game->player2->score = 0;
    game->player2->type = player2Type;
    game->player2->winner = 0;
    
    game->playerNone = (struct Player*) malloc(sizeof(struct Player));
    game->playerNone->name = "playerNone";
    game->playerNone->score = 0;
    game->playerNone->type = playerNoneType;
    game->playerNone->winner = 0;
    
    SDL_Log("%s", core->name);

    //game->message = (struct Message*) malloc(sizeof(struct Message));
    //message_init(game->message, core->render);

    game->player1->piece = (struct Piece*) malloc(sizeof(struct Piece));
    game->player1->piece->pieceType = none;
    game->player1->piece->name = "Piece1";
    piece_init(none, game->player1->piece);

    game->player2->piece = (struct Piece*) malloc(sizeof(struct Piece));
    game->player2->piece->pieceType = none;
    game->player2->piece->name = "Piece2";
    piece_init(none, game->player2->piece);
    game->player2->piece->destTextureParams.x = 300;

    game->playerNone->piece = (struct Piece*) malloc(sizeof(struct Piece));
    game->playerNone->piece->pieceType = none;
    game->playerNone->piece->name = "PieceNone";
    piece_init(none, game->playerNone->piece);
    
    game_startLoop();
    core_cleanup();

    return EXIT_SUCCESS;
}
