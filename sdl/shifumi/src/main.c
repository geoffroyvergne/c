#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <game.h>
#include <player.h>
#include <piece.h>
#include <message.h>

//struct Game game;
//struct Game *game;

int main(int argc, char** argv) {
    
    game = (struct Game*) malloc(sizeof(struct Game));
    game->name = "shifumi";
    game->width = 512;
    game->height = 512;
    game->loopDelay = 10;
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
    

    SDL_Log("%s", game->name);

    game_init();

    SDL_Texture *sdl_texture = IMG_LoadTexture(game->render, "../assets/images-set.png");

    game->message = (struct Message*) malloc(sizeof(struct Message));
    message_init(game->message, game->render);

    game->player1->piece = (struct Piece*) malloc(sizeof(struct Piece));
    game->player1->piece->pieceType = none;
    game->player1->piece->name = "Piece1";
    game->player1->piece->render = game->render;
    game->player1->piece->sdl_texture = sdl_texture;
    piece_init(none, game->player1->piece);

    game->player2->piece = (struct Piece*) malloc(sizeof(struct Piece));
    game->player2->piece->pieceType = none;
    game->player2->piece->name = "Piece2";
    game->player2->piece->render = game->render;
    game->player2->piece->sdl_texture = sdl_texture;
    piece_init(none, game->player2->piece);
    game->player2->piece->destTextureParams.x = 300;

    game->playerNone->piece = (struct Piece*) malloc(sizeof(struct Piece));
    game->playerNone->piece->pieceType = none;
    game->playerNone->piece->name = "PieceNone";
    game->playerNone->piece->render = game->render;
    game->playerNone->piece->sdl_texture = sdl_texture;
    piece_init(none, game->playerNone->piece);
    
    game_startLoop();
    game_cleanup();

    return EXIT_SUCCESS;
}
