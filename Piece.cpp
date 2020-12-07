#include "Piece.h"
#include "ChessBoard.h"

Piece::Piece(Type type, Colour colour) //
    : type(type) , colour(colour){}

Colour Piece::getColour(){ return colour; }
