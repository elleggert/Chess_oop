
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

  //DO NOT FORGET TO CHANGE THAT I'M PASSING ALL THE STRINGS AS REFERENCE AND NOT AS VALUE
  
  void submitMove(const char* source, const char* dest);

  bool correctFormat(const std::string& square);
  
  bool onBoard(const std::string& square);

  void initialiseBoard();

  void clearBoard();

  void resetBoard();

  bool isEmpty(const std:: string& square);

  bool ownPiece(const std::string& square);
  
  Colour getNextMove();
  
  void changeTurn();

  void switchGameState();

  bool isDiagonalFree(std::string const& from, std::string const& to/* std::map<std::string, Piece*>  & board*/);

bool isFileRankFree(std::string const& from, std::string const& to/* std::map<std::string, Piece*> & board */);

  bool moveExposesKing(std::string const& from, std::string const& to/* std::map<std::string, Piece*> & board */);

  bool inCheck(Colour colour /*std::map<std::string, Piece*> & board */);

  bool legalMovesLeft(Colour colour/* std::map<std::string, Piece*> & board */);

  std::string findPiece(Type type, Colour colour /*std::map<std::string, Piece*> & board */);

  
  std::string stringColour(Colour colour);

  std::string stringPiece(Type type);
  
};



  

#endif
