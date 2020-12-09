#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include <iostream>

class Pawn : public Piece {
  int move_count = 0;
  
 public:
  Pawn(Colour colour);

  std::vector<std::string> getLegalTargets(std::string const& from, std::map<std::string, Piece*> & board);


};

#endif
