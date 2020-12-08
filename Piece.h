#ifndef PIECE_H
#define PIECE_H

#include<string>
#include<map>


enum Type {UNDEFINED, KING, QUEEN, ROOK, BISHOP , KNIGHT , PAWN};
enum Colour {WHITE, BLACK};

class Piece {
  Type type = UNDEFINED;
  Colour colour = WHITE;


public:
  Piece(Type type, Colour colour);

  Colour getColour() const;
  
  Type getType() const;

  bool isOnFileRank(std::string const& from, std::string const& to);

  bool isDiagonal(std::string const& from, std::string const& to);

  bool isNextTo(std::string const& from, std::string const& to);

  bool isDiagonalFree(std::string const& from, std::string const& to, std::map<std::string, Piece*>  const& board);

  bool isFileRankFree(std::string const& from, std::string const& to, std::map<std::string, Piece*> const& board);

  virtual void print();
};

#endif
  

  
