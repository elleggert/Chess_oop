#include "Pawn.h"
#include<iostream>


Pawn::Pawn(Colour colour) //
  : Piece(PAWN, colour){}



std::vector<std::string> Pawn::getLegalTargets(std::string const& from, ChessBoard & board){
  std::string target = from, source = from;
  std::vector<std::string> legal_positions;
  int one_step = 1, two_step = 2;

  std::cout << "PAWN" << std::endl;

  if (this->getColour()){
    one_step = -1;
    two_step = -2;
  }

  if (!this->getMoveCount()){
    target[1] = from[1] + two_step;
    if (board.isFileRankFree(source, target))
      legal_positions.push_back(target);
  }

  target[1] = from[1] + one_step;
  if (board.isEmpty(target))
      legal_positions.push_back(target);
  
  target[0] = target[0] + one_step;
  if (board.onBoard(target) && !board.isEmpty(target) && !board.ownPiece(target)){
    legal_positions.push_back(target);
  }
  
  target[0] = target[0] - two_step;
  if (board.onBoard(target) && !board.isEmpty(target) && !board.ownPiece(target)){
    legal_positions.push_back(target);
  }

  if (this->getColour() == board.getNextMove()) {
    for (int i = 0 ; i < legal_positions.size(); i++){
      if (board.moveExposesKing(source, legal_positions[i]))
	legal_positions.erase(legal_positions.begin() + i);
    }
  }

  return legal_positions;
}

void Pawn::addMove(){move_count++; }

int Pawn::getMoveCount(){return move_count; }

