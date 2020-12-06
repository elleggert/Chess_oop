#include "ChessBoard.h"
#include<cctype>

using namespace std;

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

 
  


  




   

  
  
