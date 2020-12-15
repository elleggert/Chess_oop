#include "Rook.h"

Rook::Rook(Colour colour) //
  : Piece(ROOK, colour){}

std::vector<std::string> Rook::getLegalTargets(std::string const& from, ChessBoard & board){
  std::string target = "A1", source = from;
  std::vector<std::string> legal_positions;
  
  /* No named constants used to stay closer to chess notation --> legibility*/
  for ( ; target[0] <= 'H' ; ++target[0]){
    for ( ; target[1] <= '8'; ++target[1]){
      //Checking whether a given square is blocked by a piece of the same colour
      if (!board.isEmpty(target) && board.sameColour(source, target))
	continue;
      //Checking whether a given square is on the same rank or file as the source
      if (!isOnFileRank(source, target))
	continue;
      /*If the target is not adjacent, checking whether the path is free between
	source and target*/
      if (!isNextTo(source, target) && !board.isFileRankFree(source, target))
	continue;
      legal_positions.push_back(target);
    }
    target[1] = '1';
  }
  
  //Removing any destination square that would leave the king in check
  if (this->getColour() == board.getNextMove()) {
    if (!legal_positions.empty()){
      for (int i =  legal_positions.size() - 1; i >= 0; i--){
	if (board.moveExposesKing(source, legal_positions[i]))
	  legal_positions.erase(legal_positions.begin() + i);
      }
    }
  }
  return legal_positions;
}

void Rook::addMove(){move_count++; }

int Rook::getMoveCount(){return move_count; }
/*END OF FILE*/
