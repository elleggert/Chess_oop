#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "ChessBoard.h"
#include <string>
#include <vector>
#include <map>

class Bishop : public Piece {

 public:
  Bishop(Colour colour);

  std::vector<std::string> getLegalTargets(std::string const& from, ChessBoard & board);


};

#endif


