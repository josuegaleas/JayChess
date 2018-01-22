/*
 * Author: Josue Galeas
 * Last Edit: October 2, 2017
 */

#ifndef BOARD_H
#define BOARD_H

#include "Piece.hpp"
#include <map>

class Board
{
	private:
		Piece **board;
		std::string symbols[12] = {"♙", "♘", "♗", "♖", "♕", "♔", "♟", "♞", "♝", "♜", "♛", "♚"};
		std::map<char, int> mapping;
		void setPieces(int);

	public:
		Board();
		~Board();
		void setSymbol(Piece *);
		Piece *getPiece(int x, int y) const {return &board[x][y];};
		Piece *getPiece(int *) const;
};

#endif
