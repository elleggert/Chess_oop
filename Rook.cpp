#include "Rook.h"


Rook::Rook(Colour colour) //
  : Piece(ROOK, colour){}

std::vector<std::string> Rook::getLegalTargets(std::string const& from, std::map<std::string, Piece*> & board){
  std::cout << "ROOK: Only including this function as long as not all classes have a getLegalT function" << std::endl;
  std::vector<std::string> vec;
  return vec;
}
