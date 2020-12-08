#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
  int move_count = 0;
  
 public:
  Pawn(Colour colour);

  void print();


};

#endif
