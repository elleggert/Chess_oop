#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "ChessBoard.h"
#include <iostream>

class Knight : public Piece {

 public:
  Knight(Colour colour);

 std::vector<std::string> getLegalTargets(std::string const& from, ChessBoard & board);


};

#endif
