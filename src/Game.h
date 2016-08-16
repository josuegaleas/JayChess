/*
 * Author: Josue Galeas
 * Last Edit: August 16th, 2016
 */

#ifndef GAME_H
#define GAME_H
#include "Board.h"

class Game
{
	private:
		Board game;
		int *askLocation();

	public:
		void movePiece();
		void printBoard() const
		{
			game.printBoard();
		}
};

#endif
