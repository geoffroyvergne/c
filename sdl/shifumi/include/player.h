#include <stdio.h>
#include <SDL.h>
#include <piece.h>

#ifndef PLAYER
#define PLAYER

enum PlayerType {
    player1Type,
    player2Type,
    playerNoneType
};

struct Player {
    enum PlayerType type;
    char* name;
    int score;
    int winner;
    struct Piece *piece;
};

//struct Player *player;

#endif
