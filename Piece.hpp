#ifndef PIECE_H
#define PIECE_H


#include<string>
#include<map>


enum Type {UNDEFINED, KING, QUEEN, ROOK, BISHOP , KNIGHT , PAWN};
enum Colour {WHITE, BLACK};

class Piece {
  Type type = UNDEFINED;
  Colour colour = WHITE;


public:
  Piece(Type type, Colour colour) //
    : type(type) , colour(colour){}
};

#endif
  

  
