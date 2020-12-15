#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "ChessBoard.h"

class King : public Piece {
  int move_count = 0;

 public:
  King(Colour colour);

  std::vector<std::string> getLegalTargets(std::string const& from, ChessBoard & board);

  void addMove();
  int getMoveCount();
};
#endif
