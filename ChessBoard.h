
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include<map>
#include<string>
#include<iostream>
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h" 

class ChessBoard {
  std::map <std::string, Piece*> board;
  Colour next_move = WHITE;
  bool game_over = false;

 public:
  ChessBoard();
  
  void submitMove(const char* source, const char* dest);

  bool correctFormat(const std::string square);
  
  bool onBoard(const std::string square);

  void initialiseBoard();

  void clearBoard();

  void resetBoard();

  bool isEmpty(const std:: string square);

  bool ownPiece(const std::string square);

  Colour getNextMove();

  std::string stringColour(Colour colour);
};



  

#endif
