#include "Piece.h"
#include "ChessBoard.h"
#include <cstdlib>

using namespace std;

Piece::Piece(Type type, Colour colour) //
    : type(type) , colour(colour){}

Colour Piece::getColour() const { return colour; }

Type Piece::getType() const { return type; }


bool Piece::isOnFileRank(std::string const& from, std::string const& to){
  if (from[0] == to[0] || from[1] == to[1])
    return true;
  return false;
}

bool Piece::isDiagonal(std::string const& from, std::string const& to){
  if (abs(to[0] - from[0]) == abs(to[1] - from[1]))
    return true;
  return false;
}

bool Piece::isNextTo(std::string const& from, std::string const& to){
  if (abs(to[0] - from[0]) <= 1 && abs(to[1] - from[1]) <= 1)
    return true;
  return false;
}

bool Piece::isDiagonalFree(std::string const& from, std::string const& to,  std::map<string, Piece*> & board){
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
      if (board.count(small))
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
    if (board.count(small))
      return false;
  }
  return true;
}
    

bool Piece::isFileRankFree(std::string const& from, std::string const& to, std::map<string, Piece*> & board){
  int file_diff = from[0] - to[0], rank_diff = from[1] - to[1];
  string big = to, small = from;
  
  if (file_diff){
      if (file_diff < 0){
	big = from;
	small = to;
      }

    while (small != big){
      small[0]++;
      if (board.count(small))
	return false;
    }
    return true;
  }

  if (rank_diff < 0){
    big = from;
    small = to;
  }
  while (small != big){
    small[1]++;
    if (board.count(small))
      return false;
  }
  return true;
}

bool Piece::moveExposesKing(std::string const& from, std::string const& to, std::map<std::string, Piece*> & board){
  bool check_status;
  Piece* captured = nullptr;

  if (board.count(to))
    captured = board[to];

  board[to] = board[from];

  check_status = inCheck(board[from]->getColour(), board); //TO BE WRITTEN

  board[from] = board[to];

  if (captured)
    board[to] = captured;
  else board.erase(to);

  return check_status;
}


bool Piece::inCheck(Colour colour, std::map<std::string, Piece*> & board){
  string king = findPiece(KING, colour, board);
  Colour attacker = BLACK;

  if (colour == BLACK)
    attacker = WHITE;
  
  for (auto it = board.begin() ; it != board.end() ; it++){
    if (it->second->getColour() == attacker){
      vector<string> vec = it->second->getLegalTargets(it->first, board);
      if (find(vec.begin(), vec.end(), king) != vec.end())
	return true; //THE KINGS POSITION IS LEGAL FOR ONE PIECE OF THE OPPOSING TEAM -->KING IN CHECK
    }
  }
  return false; //NO PIECE CAN ATTACK THE KING
}

string Piece::findPiece(Type type, Colour colour, std::map<std::string, Piece*> & board){
  for (auto it = board.begin() ; it != board.end() ; it++){
    if (it->second->getType() == type &&
	it->second->getColour() == colour)
      return it->first;
  }
  return "NO SUCH PIECE ON THE BOARD";
}
    
   

std::vector<std::string> Piece::getLegalTargets(std::string const& from, std::map<std::string, Piece*> & board){
  std::cout << "PIECE. Only including this function as long as not all classes have a getLegalT function" << std::endl;
  std::vector<std::string> vec;
  return vec;

}
