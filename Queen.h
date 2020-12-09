#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include <iostream> //DEBUG

class Queen : public Piece {

 public:
  Queen(Colour colour);

 std::vector<std::string> getLegalTargets(std::string const& from, std::map<std::string, Piece*> & board);


};

#endif
