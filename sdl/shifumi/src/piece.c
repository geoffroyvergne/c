#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <piece.h>

void piece_init(enum PieceType pieceType, struct Piece *piece) {
    //SDL_Rect srcTextureParams = { 0, 0,  90, 90 }; // Real texture size and placement
    //piece->srcTextureParams = srcTextureParams;

    piece_togglePieceType(pieceType, piece);

    SDL_Rect destTextureParams = { 120, 120,  90, 90 }; // Texture seen in game
    piece->destTextureParams = destTextureParams;
}

void piece_togglePieceType(enum PieceType pieceType, struct Piece *piece) {
    switch(pieceType) {
        case none : 
            piece->srcTextureParams.x = 120;
            piece->srcTextureParams.y = 89;
            piece->srcTextureParams.w = 90;
            piece->srcTextureParams.h = 90;
            piece->pieceType = pieceType;
            piece->name = "none";
            break;

        case rock : 
            piece->srcTextureParams.x = 0;
            piece->srcTextureParams.y = 97;
            piece->srcTextureParams.w = 120;
            piece->srcTextureParams.h = 120;
            piece->pieceType = pieceType;
            piece->name = "rock";
            break;

        case paper : 
            piece->srcTextureParams.x = 0;
            piece->srcTextureParams.y = 0;
            piece->srcTextureParams.w = 100;
            piece->srcTextureParams.h = 90;
            piece->pieceType = pieceType;
            piece->name = "paper";
            break;

        case sissors : 
            piece->srcTextureParams.x = 100;
            piece->srcTextureParams.y = 0;
            piece->srcTextureParams.w = 120;
            piece->srcTextureParams.h = 80;
            piece->pieceType = pieceType;
            piece->name = "sissors";
            break;
    }
}

void piece_nextPiece(struct Piece *piece) {
    switch(piece->pieceType) {
        case none : 
            piece_togglePieceType(rock, piece);             
            break;

        case rock : 
            piece_togglePieceType(paper, piece);             
            break;

        case paper : 
            piece_togglePieceType(sissors, piece);             
            break;

        case sissors : 
            piece_togglePieceType(rock, piece);             
            break;
    }
}

void piece_randomPiece(struct Piece *piece) {
     int intPiece = rand() % 3 + 1;

    switch(intPiece) {
        case 1 : 
            piece_togglePieceType(rock, piece);             
            break;

        case 2 : 
            piece_togglePieceType(paper, piece);             
            break;

        case 3 : 
            piece_togglePieceType(sissors, piece);             
            break;
    }
}

void piece_display(struct Piece *piece) {
    SDL_RenderCopy(piece->render, piece->sdl_texture, &piece->srcTextureParams, &piece->destTextureParams);
}

void piece_cleanup() {

}

