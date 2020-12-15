#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include<map>
#include<string>
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h" 


/* ChessBoard class: owns all the pieces on a board and stores them in map*/
class ChessBoard {
  std::map <std::string, Piece*> board;
  Colour next_move = WHITE;
  bool game_over = false;
  
 public:
  
  /* Constructor and Destructor*/
  ChessBoard();
  ~ChessBoard();
  
  /* FUNCTIONS CALLED IN MAIN()*/
  
  /*Testing the inputs and making the moves on the board */
  void submitMove(const char* source, const char* dest);
  
  /*Clearing the board and deleting all dynamically allocated pieces*/
  void resetBoard();
  
  /* Helper functions called by the constructor, destructor and resetBoard() */
  void initialiseBoard();
  void clearBoard();
  
  /*FUNCTIONS CALLED WHEN CHECKING FOR LEGALITY OF A MOVE*/
  /*Members of the ChessBoard Class since they require knowledge of the board*/
  
  /*Checking whether a piece is blocking the path between two pieces*/
  bool isDiagonalFree(std::string const& from, std::string const& to);
  bool isFileRankFree(std::string const& from, std::string const& to);
  
  /*Checking whether a move would leave the king in check*/
  bool moveExposesKing(std::string const& from, std::string const& to);
  
  /*Checks whether a given colour is in check*/
  bool inCheck(Colour colour);
  
  /*Checks whether any piece has legal moves left -> needed for check/stalemate*/
  bool legalMovesLeft(Colour colour);
  
  /*Special function checking whether castling is legal in a given board*/
  /*Can be called by moving your king to where the Rook currently is*/
  void castling(std::string const& from, std::string const& to);
  
  /*HELPER FUNCTIONS */
  /*Boolean helper f() checking for the validity of strings */
  bool formatInvalid(const std::string& from, const std::string& to);
  bool sameColour(const std::string& from, const std::string& to);
  bool onBoard(const std::string& square);
  bool isEmpty(const std:: string& square);
  bool correctFormat(const std::string& square);
  
  /*Functions helping to print the colour or type of a piece */
  std::string stringColour(Colour colour);
  std::string stringPiece(Type type);
  
  
  /* GETTER AND SETTER FUNCTIONS FOR CHESSBOARD DATA MEMBERS*/
  
  /*Whos turn*/
  Colour getNextMove();
  
  /*Where is a given piece on the board*/
  std::string findPiece(Type type, Colour colour);
  
  /*Change the state of the game*/
  void changeTurn();
  void switchGameState();
};
#endif
/*END OF FILE*/
