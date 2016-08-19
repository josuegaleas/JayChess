/*
 * Author: Josue Galeas
 * Last Edit: August 19th, 2016
 */

#ifndef BOARD_H
#define BOARD_H
#include "ChessPiece.h"
#include "MovingPiece.h"

class Board
{
	private:
		ChessPiece board[8][8];
		void setupPieces(int);

	public:
		Board();
		MovingPiece *getPiece(int *);
		void printBoard() const;
};

#endif
