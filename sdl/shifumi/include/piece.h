#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <piece_type.h>

#ifndef PIECE
#define PIECE

struct Piece {
    char* name;
    enum PieceType pieceType;
    SDL_Rect srcTextureParams; // Real texture size and placement
    SDL_Rect destTextureParams; // Texture seen in game
    SDL_Renderer *render;
    SDL_Texture *sdl_texture;
};

//struct Piece *piece;
void piece_init(enum PieceType pieceType, struct Piece *piece);
void piece_togglePieceType(enum PieceType pieceType, struct Piece *piece);
void piece_nextPiece(struct Piece *piece);
void piece_randomPiece(struct Piece *piece);
void piece_display();
void piece_cleanup();

#endif
