/*
 * Author: Josue Galeas
 * Last Edit: August 22nd, 2016
 */

#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "MovingPiece.h"

class Game
{
	private:
		Board game;
		int *askLocation();
		bool verifyMove(MovingPiece *, MovingPiece *);
		bool verifyCapture(MovingPiece *, MovingPiece *);

	public:
		void movePiece();
		Board getBoard()
		{
			return game;
		}
};

#endif
