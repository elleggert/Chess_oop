An Object-Oriented C++ implementation of Chess. 

Begin a new game by creating a ChessBoard Instance. Moves can be executed by calling e.g. ChessBoard.submitMove("E2", "E4");

Standard Output will inform you on the outcome of that move e.g. *White's Pawn moves from E2 to E4*

Game engine checks whether a submitted move was legal, whether one colour is in check, checkmate or whether a stalemate was reached. 
Castling can be called by moving the king to the field currently occupied by the Rook and will be executed only if permitted. 

When executing ChessMain.cpp, some illegal moves are tested before simulating a game by Alexander Alekhine vs Milorad Vasić from 1931.
