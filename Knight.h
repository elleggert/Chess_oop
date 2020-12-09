#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include <iostream>

class Knight : public Piece {

 public:
  Knight(Colour colour);

 std::vector<std::string> getLegalTargets(std::string const& from, std::map<std::string, Piece*> & board);


};

#endif
