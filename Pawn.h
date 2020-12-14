#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "ChessBoard.h"

class Pawn : public Piece {
  int move_count = 0;
  
 public:
  Pawn(Colour colour);

  std::vector<std::string> getLegalTargets(std::string const& from, ChessBoard & board);

  void addMove();
  int getMoveCount();
};

#endif
