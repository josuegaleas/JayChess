/*
 * Auhor: Josue Galeas
 * Last Edit: September 12, 2017
 */

#ifndef GAME_H
#define GAME_H

#include "Board.hpp"
#include "King.hpp"
#include "Pawn.hpp"

class Game
{
	private:
		Board *board;
		King *king;
		Pawn *pawn;

	public:
		Game()
		{
			board = new Board();
			king = new King();
			pawn = new Pawn();
		};
		~Game() {delete board; delete king; delete pawn;};
		Board *getBoard() const {return board;};
		King *getKing() const {return king;};
		Pawn *getPawn() const {return pawn;};
};

#endif
