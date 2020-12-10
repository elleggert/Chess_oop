#include "ChessBoard.h"
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;


ChessBoard::ChessBoard() {initialiseBoard(); }


void ChessBoard::submitMove(const char* source, const char* dest){
  string from = source;
  string to = dest;

  if (game_over){
    cout << "The game has finished" << endl;
    return;
  }

  if (!correctFormat(from) || !correctFormat(to))
    return;

  if (!onBoard(from)){
    cout << "Source square is not on the board" << endl;
    return;
  }

  if (!onBoard(to)){
    cout << "Destination square is not on the board" << endl;
    return;
  }

  if (from == to){
    cout << "Invalid. Destination and Source square are equal. " << endl;
    return;
  }
  
  if (isEmpty(from)){
    cout << "There is no piece at position " << from << "!" << endl;
    return;
  }

  if (board[from]->getColour() != getNextMove()){
    cout << "It is not " << stringColour(board[from]->getColour())
	 << "'s turn to move!" << endl;
    return;
  }

  if (!isEmpty(to) && board[to]->getColour() == board[from]->getColour()){
    //if (castlingPossible)
  }

  vector<string> legal_targets = board[from]->getLegalTargets(from, *this);
  if (find(legal_targets.begin(), legal_targets.end(), to) == legal_targets.end()){
    cout << stringColour(board[from]->getColour()) << "'s " 
	 << stringPiece(board[from]->getType()) << " cannot move to " << to
	 <<"!" << endl;
    return;
  }

  cout << stringColour(board[from]->getColour()) << "'s "
       << stringPiece(board[from]->getType()) << " moves from "
       << from << " to " << to << endl;
  if (!isEmpty(to)){
    cout << "taking " << stringColour(board[to]->getColour()) << "'s "
	 << stringPiece(board[to]->getType()) << endl;
    delete board[to];
  }
    
  board[to] = board[from];
  board.erase(from);

  if (board[to]->getType() == KING || board[to]->getType() == ROOK || board[to]->getType() == PAWN)
    board[to]->addMove();

  cout << "Changing Turn" << endl;
  changeTurn();

  cout << "Getting Legal Moves)" << endl;
  if (!this->legalMovesLeft(getNextMove())){
    switchGameState();
    if (this->inCheck(getNextMove())){
      cout << stringColour(getNextMove()) << " is in checkmate" << endl;
      return;
    }
    cout << "Stalemate" << endl;
  }

  //WRITE PAWN AND KNIGHT
  //WRITE A VIRTUAL DESTRUCTOR FOR PIECE AND DESTRUCTORS FOR ALL PIECES
  
   return;
}



bool ChessBoard::correctFormat(const string& square){
  if (!isalpha(square[0]) || !isdigit(square[1]) || square.length() != 2){
    cout << "Input has the wrong format. " //
	 << "File: Uppercase Letter A-H. " //
	 << "Rank: Digit 1-8." << endl;
      return false;
  }
  return true;
}
  
bool ChessBoard::onBoard(const string& square){
  if (square[0] < 'A' || square[0] > 'H' || square[1] < '1' || square[1] > '8')
    return false;
  return true;
}


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
  
  //FOR DEBUGGING PURPOSES
  for (auto it = board.begin() ; it != board.end() ; it++){
    auto ptr = it->second;
    cout << it->first << endl;
  }
  
  cout << "A new chess game is started!" << endl;
}

 
  
void ChessBoard::clearBoard(){
  for (auto it = board.begin() ; it != board.end() ; it++)
    delete it->second;
  board.clear();
}


void ChessBoard::resetBoard(){
  next_move = WHITE;
  game_over = false;
  clearBoard();
  initialiseBoard();
}


bool ChessBoard::isEmpty(const string& square){
  map<string, Piece*>::iterator it;
  it = board.find(square);
  if (it == board.end())
    return true;
  return false;
 }

 bool ChessBoard::ownPiece(const string& square){
   map<string, Piece*>::iterator it;
   it = board.find(square);
   if (it->second->getColour() == next_move)
     return true;
   return false;
 }

 
Colour ChessBoard::getNextMove(){return next_move; }

string ChessBoard::stringColour(Colour colour){
  if (colour == WHITE)
    return "White";
  return "Black";
}

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

void ChessBoard::changeTurn(){
  if (next_move == WHITE){
    next_move = BLACK;
    return;
  }
  next_move = WHITE;
  return;
}

void ChessBoard::switchGameState(){game_over = true; }

bool ChessBoard::isDiagonalFree(std::string const& from, std::string const& to){
  int file_diff = from[0] - to[0], rank_diff = from[1] - to[1];
  string big = to, small = from;
  
  if (file_diff == rank_diff){
    if (file_diff > 0){
      big = from;
      small = to;
    }
    while (small != big){
      small[0]++;
      small[1]++;
      if (!this->isEmpty(small))
	return false;
    }
    return true;
  }
  if (file_diff > 0){
    big = from;
    small = to;
  }
  while (small != big){
    small[0]++;
    small[1]--;
    if (!this->isEmpty(small))
      return false;
  }
  return true;
}
    

bool ChessBoard::isFileRankFree(std::string const& from, std::string const& to){
  int file_diff = from[0] - to[0], rank_diff = from[1] - to[1];
  string big = to, small = from;
  
  if (file_diff){
      if (file_diff > 0){
	big = from;
	small = to;
      }

    while (small != big){
      small[0]++;
      if (!this->isEmpty(small))
	return false;
    }
    return true;
  }

  if (rank_diff > 0){
    big = from;
    small = to;
  }
  while (small != big){
    small[1]++;
    if (!this->isEmpty(small))
      return false;
  }
  return true;
}

bool ChessBoard::moveExposesKing(std::string const& from, std::string const& to){
  bool check_status;
  Piece* captured = nullptr;

  if (!this->isEmpty(to))
    captured = board[to];

  board[to] = board[from];
  board.erase(from);

  check_status = this->inCheck(board[to]->getColour()); //TO BE WRITTEN

  board[from] = board[to];

  if (captured)
    board[to] = captured;
  else board.erase(to);

  return check_status;
}


bool ChessBoard::inCheck(Colour colour){
  string king = findPiece(KING, colour);
  Colour attacker = BLACK;

  if (colour == BLACK)
    attacker = WHITE;
  
  for (auto it = board.begin() ; it != board.end() ; it++){
    if (it->second->getColour() == attacker){
      vector<string> vec = it->second->getLegalTargets(it->first, *this);
      if (find(vec.begin(), vec.end(), king) != vec.end())
	return true; //THE KINGS POSITION IS LEGAL FOR ONE PIECE OF THE OPPOSING TEAM -->KING IN CHECK
    }
  }
  return false; //NO PIECE CAN ATTACK THE KING
}


bool ChessBoard::legalMovesLeft(Colour colour){
  for (auto it = board.begin() ; it != board.end() ; it++){
    if (it->second->getColour() == colour){
      vector<string> vec = it->second->getLegalTargets(it->first, *this);
      if (!vec.empty())
	return true;
    }
  }
  return false;
}


string ChessBoard::findPiece(Type type, Colour colour){
  for (auto it = board.begin() ; it != board.end() ; it++){
    if (it->second->getType() == type &&
	it->second->getColour() == colour)
      return it->first;
  }
  return "NO SUCH PIECE ON THE BOARD";
}


  
  
