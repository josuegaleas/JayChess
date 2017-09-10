/*
 * Author: Josue Galeas
 * Last Edit: September 9, 2017
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
		~Board() {delete[] board;};
		Piece *getPiece(int, int) const;
		Piece *getPiece(int *) const;
		void drawBoard() const;
};

#endif
