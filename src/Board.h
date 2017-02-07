/*
 * Author: Josue Galeas
 * Last Edit: Feb 6, 2017
 */

#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
/* #include "ActivePiece.h" */

class Board
{
	private:
		Piece board[8][8];
		void setupPieces(int);
		void setupSymbols();

	public:
		Board();
		/* ActivePiece *getActivePiece(int *); */
		Piece *getPiece(int, int);
		void printBoard() const;
		void drawBoard() const;
};

#endif
