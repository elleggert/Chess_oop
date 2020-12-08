#include "Pawn.h"
#include<iostream>


Pawn::Pawn(Colour colour) //
  : Piece(PAWN, colour){}

void Pawn::print() {std::cout << "This was called on the Pawn Class" << std::endl; }
