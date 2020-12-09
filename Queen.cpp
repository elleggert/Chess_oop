#include "Queen.h"


Queen::Queen(Colour colour) //
  : Piece(QUEEN, colour){}


std::vector<std::string> Queen::getLegalTargets(std::string const& from, std::map<std::string, Piece*> & board){
  std::cout << "QUEEN: Only including this function as long as not all classes have a getLegalT function" << std::endl;
  std::vector<std::string> vec;
  return vec;
}
