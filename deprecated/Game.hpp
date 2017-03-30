/*
 * Author: Josue Galeas
 * Last Edit: August 23rd, 2016
 */

#ifndef GAME_H
#define GAME_H
#include "Board.hpp"
#include "ActivePiece.hpp"

class Game
{
	private:
		Board chessBoard;
		int *askLocation();
		bool verifyMove(ActivePiece *, ActivePiece *);
		bool verifyCapture(ActivePiece *, ActivePiece *);

	public:
		void movePiece();
		Board getBoard()
		{
			return chessBoard;
		}
};

#endif
