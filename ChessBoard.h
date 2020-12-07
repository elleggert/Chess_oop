
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include<map>
#include<string>
#include<iostream>
#include "Piece.h"


class ChessBoard {
  map <string, Piece*> board;
  Colour next_move = WHITE;
  bool game_over = false;

 public:
  ChessBoard();
  
  void submitMove(const char* source, const char* dest);

  bool correctFormat(const std::string square);
  
  bool onBoard(const std::string square);

  void initialiseBoard();

};



  

#endif
