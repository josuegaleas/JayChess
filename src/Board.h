/*
 * Author: Josue Galeas
 * Last Edit: August 23rd, 2016
 */

#ifndef BOARD_H
#define BOARD_H
#include "ChessPiece.h"
#include "ActivePiece.h"

class Board
{
	private:
		ChessPiece board[8][8];
		void setupPieces(int);

	public:
		Board();
		ActivePiece *getActivePiece(int *);
		ChessPiece *getChessPiece(int, int);
		void printBoard() const;
};

#endif
