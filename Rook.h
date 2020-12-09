#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include <iostream> //DEBUG

class Rook : public Piece  {
  int move_count = 0;

 public:
  Rook(Colour colour);
  
  std::vector<std::string> getLegalTargets(std::string const& from, std::map<std::string, Piece*> & board);


};

#endif
