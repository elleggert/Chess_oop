#include "Knight.h"
#include <cstdlib>


Knight::Knight(Colour colour) //
  : Piece(KNIGHT, colour){}

std::vector<std::string> Knight::getLegalTargets(std::string const& from, ChessBoard & board){
  std::string target = "A1", source = from;
  std::vector<std::string> legal_positions;

  std::cout << "KNIGHT" << std::endl;
  for ( ; target[0] <= 'H' ; ++target[0]){
    for ( ; target[1] <= '8'; ++target[1]){
      //Checking whether a given square is blocked by a piece of the same colour
      if (!board.isEmpty(target) && board.ownPiece(target))
	continue;
      //Checking whether a given square is on the same rank or file as the source
      if (isOnFileRank(source, target) || isDiagonal(source, target))
	continue;
      //Checking whether it is the closest possible piece
      if (abs(source[0] - target[0]) > 2 || abs(source[1] - target[1]) > 2)
	continue;
	//Check whether king is left exposed by move
    }
    target[1] = '1';
  }
  if (this->getColour() == board.getNextMove()) {
    for (int i = 0 ; i < legal_positions.size(); i++){
      if (board.moveExposesKing(source, legal_positions[i]))
	legal_positions.erase(legal_positions.begin() + i);
    }
  }
  
  return legal_positions;
}
