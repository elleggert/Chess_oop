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

    

std::vector<std::string> Piece::getLegalTargets(std::string const& from, ChessBoard & board){
  std::cout << "PIECE. Only including this function as long as not all classes have a getLegalT function" << std::endl;
  std::vector<std::string> vec;
  return vec;

}

void Piece::addMove(){}
