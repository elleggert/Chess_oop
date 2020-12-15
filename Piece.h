#ifndef PIECE_H
#define PIECE_H

#include<string>
#include<map>
#include<vector>

enum Colour {WHITE, BLACK};
enum Type {UNDEFINED, KING, QUEEN, ROOK, BISHOP , KNIGHT , PAWN};


class ChessBoard;

/* Piece Class: Stores information on colour and type*/
/* Base Class for the derived classes of all pieces*/
class Piece {
  Type type = UNDEFINED;
  Colour colour = WHITE;
  
 public:
  
  /*Constructor -> all derived class constructors delegate to this one*/
  Piece(Type type, Colour colour);
  
  /*Virtual destructor*/
  virtual ~Piece();
  
  
  /*Getter Functions for attributes*/
  Colour getColour() const;
  Type getType() const;
  
  /*Functions called when testing for legal positions
    Not a member of chessboard since they do not need information on the board*/
  bool isOnFileRank(std::string const& from, std::string const& to);
  bool isDiagonal(std::string const& from, std::string const& to);
  bool isNextTo(std::string const& from, std::string const& to);
  
  /* The function getLegalTarget() returns a vector with all legal squares
     that can be reached by a Piece from a specific position.
     Every piece has a different implementation depending on the chess rules */
  
  /*NOTE: Returning the vector by value is a conscious design decision, based on
    the fact that any compiler adhering to c++11 has vector copy elision.
    The alternative (creating a vector and passing it by reference) would waste 
    memory space, since in legalMovesLeft(), getLegalMoves() is called repeatedly.
    Since vector.clear() only deletes the elements but does not resize the vector,
    the vector would become larger than it needs to be  -> wasteful.*/
  
  virtual std::vector<std::string> getLegalTargets(std::string const& from, ChessBoard & board);
 
  /* Virtual functions for the move_count attribute
     Only a member of Pawn, Rook and King derived Classes*/
  virtual void addMove();
  virtual int getMoveCount();
};
#endif
/*END OF FILE*/
