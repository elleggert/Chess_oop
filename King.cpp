#include "King.h"


King::King(Colour colour) //
  : Piece(KING, colour){}


std::vector<std::string> King::getLegalTargets(std::string const& from, std::map<std::string, Piece*> & board){
  std::cout << "KING: Only including this function as long as not all classes have a getLegalT function" << std::endl;
  std::vector<std::string> vec;
  return vec;
}
