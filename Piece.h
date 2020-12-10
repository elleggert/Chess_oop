#ifndef PIECE_H
#define PIECE_H

#include<string>
#include<map>
#include<vector>

enum Colour {WHITE, BLACK};
enum Type {UNDEFINED, KING, QUEEN, ROOK, BISHOP , KNIGHT , PAWN};


class ChessBoard;

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

  virtual std::vector<std::string> getLegalTargets(std::string const& from, ChessBoard & board);

  virtual void addMove();
};

#endif
  

  
