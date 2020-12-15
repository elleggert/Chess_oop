#include "Pawn.h"

Pawn::Pawn(Colour colour) //
  : Piece(PAWN, colour){}

std::vector<std::string> Pawn::getLegalTargets(std::string const& from, ChessBoard & board){
  std::string target = from, source = from;
  std::vector<std::string> legal_positions;
  int one_step = 1, two_step = 2;
  
  //Check Colour
  if (this->getColour()){
    one_step = -1;
    two_step = -2;
  }
  
  //Check whether pawn has already moved for validity of opening move
  if (!this->getMoveCount()){
    target[1] = from[1] + two_step;
    if (board.isFileRankFree(source, target))
      legal_positions.push_back(target);
  }
  
  //Add normal move
  target[1] = from[1] + one_step;
  if (board.isEmpty(target))
    legal_positions.push_back(target);
  
  //Check whether an opposing piece can be taken
  target[0] = target[0] + one_step;
  if (board.onBoard(target) && !board.isEmpty(target) && !board.sameColour(source, target)){
    legal_positions.push_back(target);
  }
  
  target[0] = target[0] - two_step;
  if (board.onBoard(target) && !board.isEmpty(target) && !board.sameColour(source, target)){
    legal_positions.push_back(target);
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
/*End of function*/

void Pawn::addMove(){move_count++; }

int Pawn::getMoveCount(){return move_count; }
/*END OF FILE*/
