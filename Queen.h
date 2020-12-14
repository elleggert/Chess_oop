#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "ChessBoard.h"

class Queen : public Piece {

 public:
  Queen(Colour colour);

  std::vector<std::string> getLegalTargets(std::string const& from, ChessBoard & board);


};

#endif
