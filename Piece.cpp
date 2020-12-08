#include "Piece.h"
#include "ChessBoard.h"
#include<cstdlib>

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

bool Piece::isDiagonalFree(std::string const& from, std::string const& to,  std::map<string, Piece*> const& board){
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
    

bool Piece::isFileRankFree(std::string const& from, std::string const& to, std::map<string, Piece*> const& board){
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

    

  
void Piece::print() {std::cout << "This was called on the Piece Class" << std::endl; }
