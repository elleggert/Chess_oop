#include "ChessBoard.h"
#include <cctype>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

ChessBoard::ChessBoard() {initialiseBoard(); }

ChessBoard::~ChessBoard() {clearBoard(); }


void ChessBoard::submitMove(const char* source, const char* dest){
  string from = source;
  string to = dest;

  //Test whether game is still unfinished
  if (game_over){
    cout << "The game has finished" << endl;
    return;
  }

  //Test if inputs were correctly specified i.e. on board, only two digits etc.
  if(formatInvalid(from, to))
    return;
  
  //Test for whether a square is taken by a piece
  if (isEmpty(from)){
    cout << "There is no piece at position " << from << "!" << endl;
    return;
  }
  
  // Test for whether player whos turn it is has moved
  if (board[from]->getColour() != getNextMove()){
    cout << "It is not " << stringColour(board[from]->getColour())
	 << "'s turn to move!" << endl;
    return;
  }
  
  //Special case: Has Castling been called and is it currently legal?
  //(Castling be called by moving the king to the position of one of the rooks. 
  if (!isEmpty(to) && board[to]->getColour() == board[from]->getColour()){
    if (board[from]->getType() == KING && board[to]->getType() == ROOK){
      castling(from, to);
      return;
    }
  }
  
  //Getting all legal targets for the piece on the source square
  //If destination square not in the vector --> illegal move
  vector<string> targets = board[from]->getLegalTargets(from, *this);
  if (find(targets.begin(), targets.end(), to) == targets.end()){
    cout << stringColour(board[from]->getColour()) << "'s " 
	 << stringPiece(board[from]->getType()) << " cannot move to " << to
	 <<"!" << endl;
    return;
  }
  
  //Make the actual move if it is legal. Capture a piece if necessary*/
  cout << stringColour(board[from]->getColour()) << "'s "
       << stringPiece(board[from]->getType()) << " moves from "
       << from << " to " << to;
  if (!isEmpty(to)){
    cout << " taking " << stringColour(board[to]->getColour()) << "'s "
	 << stringPiece(board[to]->getType());
    delete board[to];
  }
  cout << endl;
  
  board[to] = board[from];
  board.erase(from);
  
  //Update move count for certain pieces (needed for castling and pawn opening)
  if (board[to]->getType() == KING ||
      board[to]->getType() == ROOK ||
      board[to]->getType() == PAWN)
    board[to]->addMove();
  
  //Switch turns and test whether the game has reached stalemate or checkmate
  changeTurn();      

  if (!this->legalMovesLeft(getNextMove())){
    switchGameState();
    if (this->inCheck(getNextMove())){
      cout << stringColour(getNextMove()) << " is in checkmate" << endl;
      return;
    }
    cout << "The game has ended in a stalemate" << endl;
    return;
  }

  //Inform a player that its king in check
  if (this->inCheck(getNextMove()))
    cout << stringColour(getNextMove()) << " is in check" << endl;
  return;
}
/* End of function*/

void ChessBoard::resetBoard(){
  next_move = WHITE;
  game_over = false;
  clearBoard();
  initialiseBoard();
}
/* End of function*/

void ChessBoard::initialiseBoard(){
  string square;
  
  //WHITE
  for(square = "A2"; square[0] <= 'H'; ++square[0])
    board[square] = new Pawn(WHITE);
  
  board["A1"] = new Rook(WHITE);
  board["B1"] = new Knight(WHITE);
  board["C1"] = new Bishop(WHITE);
  board["D1"] = new Queen(WHITE);
  board["E1"] = new King(WHITE);
  board["F1"] = new Bishop(WHITE);
  board["G1"] = new Knight(WHITE);
  board["H1"] = new Rook(WHITE);
  
  //BLACK
  for(square = "A7"; square[0] <= 'H'; ++square[0])
    board[square] = new Pawn(BLACK);
  
  board["A8"] = new Rook(BLACK);
  board["B8"] = new Knight(BLACK);
  board["C8"] = new Bishop(BLACK);
  board["D8"] = new Queen(BLACK);
  board["E8"] = new King(BLACK);
  board["F8"] = new Bishop(BLACK);
  board["G8"] = new Knight(BLACK);
  board["H8"] = new Rook(BLACK);
  
  cout << "A new chess game is started!" << endl;
}
/* End of function*/

void ChessBoard::clearBoard(){
  for (auto it = board.begin() ; it != board.end() ; it++)
    delete it->second;
  board.clear();
}
/* End of function*/

bool ChessBoard::isDiagonalFree(std::string const& from, std::string const& to){
  int file_diff = from[0] - to[0], rank_diff = from[1] - to[1];
  string big = to, small = from;
  
  if (file_diff == rank_diff){
    if (file_diff > 0){
      big = from;
      small = to;
    }
    small[0]++;
    small[1]++;
    while (small != big){
      if (!this->isEmpty(small))
	return false;
      small[0]++;
      small[1]++;
    }
    return true;
  }
  if (file_diff > 0){
    big = from;
    small = to;
  }
  small[0]++;
  small[1]--;
  while (small != big){
    if (!this->isEmpty(small))
      return false;
    small[0]++;
    small[1]--;
  }
  return true;
}
/* End of function*/

bool ChessBoard::isFileRankFree(std::string const& from, std::string const& to){
  int file_diff = from[0] - to[0], rank_diff = from[1] - to[1];
  string big = to, small = from;
  
  if (file_diff){
    if (file_diff > 0){
      big = from;
      small = to;
    }
    
    small[0]++;
    while (small != big){
      if (!this->isEmpty(small))
	return false;
      small[0]++;
    }
    return true;
  }
  
  if (rank_diff > 0){
    big = from;
    small = to;
  }
  small[1]++;
  while (small != big){
    if (!this->isEmpty(small))
      return false;
    small[1]++;
  }
  return true;
}
/* End of function*/

bool ChessBoard::moveExposesKing(std::string const& from, std::string const& to){
  bool check_status;
  Piece* captured = nullptr;
  
  //Store current board information
  if (!this->isEmpty(to))
    captured = board[to];
  
  //Simulate the move
  board[to] = board[from];
  board.erase(from);
  
  //See whether this leads to check
  check_status = this->inCheck(board[to]->getColour()); 
  
  //Revert changes
  board[from] = board[to];
  
  if (captured)
    board[to] = captured;
  else board.erase(to);
  
  return check_status;
}
/* End of function*/

bool ChessBoard::inCheck(Colour colour){
  string king = findPiece(KING, colour);
  Colour attacker = BLACK;
  
  if (colour == BLACK)
    attacker = WHITE;
  
  for (auto it = board.begin() ; it != board.end() ; it++){
    if (it->second->getColour() == attacker){
      vector<string> vec = it->second->getLegalTargets(it->first, *this);
      if (find(vec.begin(), vec.end(), king) != vec.end())
	return true; //If Kings position legal for one opposing piece -> check
    }
  }
  return false; //No piece can attack the king --> no check
}
/* End of function*/

bool ChessBoard::legalMovesLeft(Colour colour){
  std::string target = "A1";

  /* For Chess, I deliberately chose to not use named constants for file/rank, 
     since I found the code to be closer to chess notation and thus more legible*/
  
  for ( ; target[0] <= 'H' ; ++target[0]){
    for ( ; target[1] <= '8'; ++target[1]){
      if (!isEmpty(target) && board[target]->getColour() == colour){
	vector<string> targets = board[target]->getLegalTargets(target, *this);
	//True once one piece has a legal move (i.e. no check) left
	if (targets.size())
	  return true;
      }
    }
    target[1] = '1';
  }
  //False otherwise
  return false;
}
/* End of function*/

void ChessBoard::castling(std::string const& from, std::string const& to){
  string target = from;
  
  if (board[from]->getMoveCount() || board[to]->getMoveCount()){
    cout << "Invalid: Castling only legal when either piece has not yet moved "
	 << endl;
    return;
  }
  
  if (inCheck(board[from]->getColour())){
    cout << "Invalid: Cannot castle when in check" << endl;
    return;
  }
  
  if (!isFileRankFree(from, to)){
    cout << "Invalid: Cannot castle with pieces between King and Rook" << endl;
    return;
  }
  
  //QUEENSIDE
  if (to[0] < from[0]){
    target[0]--;
    if (moveExposesKing(from, target)){
      cout << "Invalid: Cannot castle through check" << endl;
      return;
    }
    
    target[0]--;
    if (moveExposesKing(from, target)){
      cout << "Invalid: Cannot castle into check" << endl;
      return;
    }
    
    board[from]->addMove();
    board[to]-> addMove();
    board[target] = board[from];
    target[0]++;
    board[target] = board[to];
    board.erase(from);
    board.erase(to);
    
    cout << stringColour(board[target]->getColour())
	 << " has completed queenside castling "<< endl;
  }
  
  //KINGSIDE
  if (to[0] > from[0]){
    target[0]++;
    if (moveExposesKing(from, target)){
      cout << "Invalid: Cannot castle through check" << endl;
      return;
    }
    
    target[0]++;
    if (moveExposesKing(from, target)){
      cout << "Invalid: Cannot castle into check" << endl;
      return;
    }
    
    board[from]->addMove();
    board[to]-> addMove();
    board[target] = board[from];
    target[0]--;
    board[target] = board[to];
    board.erase(from);
    board.erase(to);
    
    cout << stringColour(board[target]->getColour())
	 << " has completed kingside castling "<< endl;
  }
  changeTurn();
  
  //Also need to check for checkmate, check and stalemate afterwards
  //Castling will almost never result in checkmate, but theoretically possible
  if (!this->legalMovesLeft(getNextMove())){
    switchGameState();
    if (this->inCheck(getNextMove())){
      cout << stringColour(getNextMove()) << " is in checkmate" << endl;
      return;
    }
    cout << "The game has ended in a stalemate" << endl;
    return;
  }
  
  if (this->inCheck(getNextMove()))
    cout << stringColour(getNextMove()) << " is in check" << endl;
  return;
}
/* End of function*/

bool ChessBoard::formatInvalid(const string& from, const string& to){
  if (!correctFormat(from) || !correctFormat(to))
    return true;
  
  if (!onBoard(from)){
    cout << "Source square is not on the board" << endl;
    return true;
  }
  
  if (!onBoard(to)){
    cout << "Destination square is not on the board" << endl;
    return true;
  }
  
  if (from == to){
    cout << "Invalid. Destination and Source square are equal. " << endl;
    return true;
  }
  return false;
}
/* End of function*/


bool ChessBoard::sameColour(const string& from, const string& to){
  if (board[from]->getColour() == board[to]->getColour())
    return true;
  return false;
}
/* End of function*/

bool ChessBoard::onBoard(const string& square){
  if (square[0] < 'A' || square[0] > 'H' || square[1] < '1' || square[1] > '8')
    return false;
  return true;
}
/* End of function*/

bool ChessBoard::isEmpty(const string& square){
  map<string, Piece*>::iterator it;
  it = board.find(square);
  if (it == board.end())
    return true;
  return false;
}
/* End of function*/

bool ChessBoard::correctFormat(const string& square){
  if (!isalpha(square[0]) || !isdigit(square[1]) || square.length() != 2){
    cout << "Input has the wrong format. " //
	 << "File: Uppercase Letter A-H. " //
	 << "Rank: Digit 1-8." << endl;
    return false;
  }
  return true;
}
/* End of function*/

string ChessBoard::stringColour(Colour colour){
  if (colour == WHITE)
    return "White";
  return "Black";
}
/* End of function*/

string ChessBoard::stringPiece(Type type){
  switch (type){
  case 1: return "King"; 
  case 2: return "Queen";
  case 3: return "Rook";
  case 4: return "Bishop";
  case 5: return "Knight";
  case 6: return "Pawn";
  default: return "Piece";
  }
}
/* End of function*/

Colour ChessBoard::getNextMove(){return next_move; }

string ChessBoard::findPiece(Type type, Colour colour){
  for (auto it = board.begin() ; it != board.end() ; it++){
    if (it->second->getType() == type &&
	it->second->getColour() == colour)
      return it->first;
  }
  cout << "No such piece on the board" << endl;
  return "";
}
/* End of function*/

void ChessBoard::changeTurn(){
  if (next_move == WHITE){
    next_move = BLACK;
    return;
  }
  next_move = WHITE;
  return;
}
/* End of function*/

void ChessBoard::switchGameState(){game_over = true; }

/* END OF FILE*/
