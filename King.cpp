#include "King.h"
#include <iostream> //DEBUG

King::King(Colour colour) //
  : Piece(KING, colour){}


std::vector<std::string> King::getLegalTargets(std::string const& from, ChessBoard & board){
  std::string target = "A1", source = from;
  std::vector<std::string> legal_positions;

  for ( ; target[0] <= 'H' ; ++target[0]){
    for ( ; target[1] <= '8'; ++target[1]){
      // Checking whether a given square is next to the current position of the king
       if (!isNextTo(source, target))
	continue;
      //Checking whether a given square is blocked by a piece of the same colour
       if (!board.isEmpty(target) && board.sameColour(source, target))
	continue;
      //Simulate the move and test whether it leaves the king in CHECK
      legal_positions.push_back(target);
    }
    target[1] = '1';
  }

 if (this->getColour() == board.getNextMove()) {
    if (!legal_positions.empty()){
      for (int i =  legal_positions.size() - 1; i >= 0; i--){
      if (board.moveExposesKing(source, legal_positions[i]))
	legal_positions.erase(legal_positions.begin() + i);
      }
    }
  }
 /*
  if (this->getColour() == board.getNextMove()) {
    for (int i = 0 ; i < legal_positions.size(); i++){
      if (board.moveExposesKing(source, legal_positions[i]))
	legal_positions.erase(legal_positions.begin() + i);
    }
  }

 */
  return legal_positions;
}

void King::addMove(){move_count++; }

int King::getMoveCount(){return move_count; }
