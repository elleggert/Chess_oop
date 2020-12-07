#include "ChessBoard.h"
#include<cctype>

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
   return;
}

bool ChessBoard::correctFormat(const string square){
  if (!isalpha(square[0]) || !isdigit(square[1]) || square.length() != 2){
    cout << "Input has the wrong format. " //
	 << "File: Uppercase Letter A-H. " //
	 << "Rank: Digit 1-8." << endl;
      return false;
  }
  return true;
}
  
bool ChessBoard::onBoard(const string square){
  if (square[0] < 'A' || square[0] > 'H' || square[1] < '1' || square[1] > '8')
    return false;
  return true;
}

void ChessBoard::initialiseBoard(){
  string square;
  
  //white pieces (piece default colour is white)
  board["A1"] = new Rook(WHITE);
  board["H1"] = new Rook(WHITE);
  board["B1"] = new Knight(WHITE);
  board["G1"] = new Knight(WHITE);
  board["C1"] = new Bishop(WHITE);
  board["F1"] = new Bishop(WHITE);
  board["D1"] = new Queen(WHITE);
  board["E1"] = new King(WHITE);
  for(square = "A2"; square[0] <= 'H'; ++square[0])
    board[square] = new Pawn(WHITE);

  //black pieces
  board["A8"] = new Rook(BLACK);
  board["H8"] = new Rook(BLACK);
  board["B8"] = new Knight(BLACK);
  board["G8"] = new Knight(BLACK);  
  board["C8"] = new Bishop(BLACK);
  board["F8"] = new Bishop(BLACK);
  board["D8"] = new Queen(BLACK);
  board["E8"] = new King(BLACK);
  for(square = "A7"; square[0] <= 'H'; ++square[0])
    board[coord] = new Pawn(BLACK);

  cout << "A new chess game is started!" << endl;
}

 
  


  




   

  
  
