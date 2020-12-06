
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include<map>
#include<string>
#include<iostream>


class ChessBoard {
  //map<string, Piece*> board;
  bool white_turn = true;
  bool game_over = false;

 public:
  void submitMove(const char* source, const char* dest);

  bool correctFormat(const std::string square);
  
  bool onBoard(const std::string square);

};



  

#endif
