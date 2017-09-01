/*
 * Author: Josue Galeas
 * Last Edit: April 13, 2017
 */

#ifndef BOARD_H
#define BOARD_H

#include "Piece.hpp"

class Board
{
	private:
		Piece *board;
		void setupPieces(int);
		void setupSymbols();

	public:
		Board();
		~Board();
		Piece *getBoard() const {return board;};
		Piece *getPiece(int, int) const;
		Piece *getPiece(int *) const;
		void printBoard() const;
		void drawBoard() const;
};

#endif
