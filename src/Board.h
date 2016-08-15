/*
 * Author: Josue Galeas
 * Last Edit: August 15th, 2016
 */

#ifndef BOARD_H
#define BOARD_H
#include "ChessPiece.h"

class Board
{
	private:
		ChessPiece board[8][8];
		// Linked list for moves done?
		void setPieces(int);

	public:
		Board();
		char *getPiece(int, int);
		void movePiece();
		void printBoard() const;
};

#endif
