#include "Pawn.h"
#include<iostream>


Pawn::Pawn(Colour colour) //
  : Piece(PAWN, colour){}

//void Pawn::print() {std::cout << "This was called on the Pawn Class" << std::endl; }


std::vector<std::string> Pawn::getLegalTargets(std::string const& from, std::map<std::string, Piece*> & board){
  std::cout << "PAWN: Only including this function as long as not all classes have a getLegalT function" << std::endl;
  std::vector<std::string> vec;
  return vec;
}
