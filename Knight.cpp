#include "Knight.h"


Knight::Knight(Colour colour) //
  : Piece(KNIGHT, colour){}

std::vector<std::string> Knight::getLegalTargets(std::string const& from, std::map<std::string, Piece*> & board){
  std::cout << "KNIGHT: Only including this function as long as not all classes have a getLegalT function" << std::endl;
  std::vector<std::string> vec;
  return vec;
}
