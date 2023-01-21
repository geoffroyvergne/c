#include <stdio.h>
#include <SDL.h>
#include <player.h>

#ifndef GAME
#define GAME

struct Game {        
    int partyNumber;    
    struct Player *player1;
    struct Player *player2;
    struct Player *playerNone;
    //struct Message *message;
    enum PlayerType winner;
};

struct Game *game;

void game_init();
void game_renderView();
void game_startLoop();

void game_result();
void game_setWinner(enum PlayerType type);
struct Player* game_getWinner(enum PlayerType type);
char* game_getScore();
void game_newGame();

void game_cleanup();

#endif
