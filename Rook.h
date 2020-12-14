#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "ChessBoard.h"

class Rook : public Piece  {
  int move_count = 0;

 public:
  Rook(Colour colour);
  
  std::vector<std::string> getLegalTargets(std::string const& from, ChessBoard & board);
  
  void addMove();
  int getMoveCount();
};

#endif
