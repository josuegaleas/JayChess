/*
 * Author: Josue Galeas
 * Last Edit: August 13th, 2016
 */

#ifndef BOARD_H
#define BOARD_H
#include "ChessPiece.h"

class Board
{
	private:
		ChessPiece board[8][8];
		void setPieces(int);

	public:
		Board();
		void printBoard() const;
};

#endif
