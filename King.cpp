#include "King.h"
#include <iostream> //DEBUG

King::King(Colour colour) //
  : Piece(KING, colour){}


std::vector<std::string> King::getLegalTargets(std::string const& from, std::map<std::string, Piece*> & board){
  std::string target = "A1", source = from;
  std::vector<std::string> legal_positions;

  std::cout << "KING" << std::endl;
  for ( ; target[0] <= 'H' ; ++target[0]){
    for ( ; target[1] <= '8'; ++target[1]){
      // Checking whether a given square is next to the current position of the king
       if (!isNextTo(source, target))
	continue;
      //Checking whether a given square is blocked by a piece of the same colour
      if (board.count(target) && board[target]->getColour() == board[source]->getColour())
	continue;
      //Simulate the move and test whether it leaves the king in CHECK
      if (moveExposesKing(source, target, board))
	continue;
      legal_positions.push_back(target);
    }
    target[1] = '1';
  }

  return legal_positions;
}

