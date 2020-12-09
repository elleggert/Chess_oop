#include "Rook.h"


Rook::Rook(Colour colour) //
  : Piece(ROOK, colour){}

std::vector<std::string> Rook::getLegalTargets(std::string const& from, std::map<std::string, Piece*> & board){
  std::string target = "A1", source = from;
  std::vector<std::string> legal_positions;
  
  std::cout << "KNIGHT" << std::endl;
  for ( ; target[0] <= 'H' ; ++target[0]){
    for ( ; target[1] <= '8'; ++target[1]){
      //Checking whether a given square is blocked by a piece of the same colour
      if (board.count(target) && board[target]->getColour() == board[source]->getColour())
	continue;
      //Checking whether a given square is on the same rank or file as the source
      if (!isOnFileRank(source, target))
	continue;
      //If the target is not adjacent, checking whether the path is free between source and target
      if (!isNextTo(source, target) && !isFileRankFree(source, target, board))
	continue;
      if (moveExposesKing(source, target, board))
	continue;
      legal_positions.push_back(target);
    }
    target[1] = '1';
  }
  
  return legal_positions;
}

