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

  vector<string> legal_targets = board[from]->getLegalTargets(from, board);
  if (find(legal_targets.begin(), legal_targets.end(), to) == legal_targets.end()){
    cout << stringColour(board[from]->getColour()) << "'s " 
	 << stringPiece(board[from]->getType()) << " cannot move to " << to <<"!" << endl;
    return;
  }

  cout << stringColour(board[from]->getColour()) << "'s "
       << stringPiece(board[from]->getType()) << "moves from "
       << from << " to " << to;
  if (!isEmpty(to)){
    cout << "taking " << stringColour(board[to]->getColour()) << "'s "
	 << stringPiece(board[to]->getType()) << endl;
    delete board[to];
  }
    
  board[to] = board[from];
  
      //for (auto it = board.begin() ; it != board.end() ; it++)
      // board[it->first]->print();

    // CHECK WHETHER BOARD IS IN CHECK
    //IF YES CHECK FOR CHECKMATE
    //IsCheckmate --> GO throug ALL PIECES AND SEE WHETHER ANY HAS A MOVE LEFT
    //IS STALEMATE -->
  //DO NOT FORGET TO SWITCH PLAYERS
  //DO NOT FORGET TO UPDATE THE MOVE COUNT IF THE PIECE I MOVE WAS KING; ROOK OR PAWN
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

   

  
  
