/*
 * Auhor: Josue Galeas
 * Last Edit: September 29, 2017
 */

#ifndef GAME_H
#define GAME_H

#include "King.hpp"
#include "Pawn.hpp"

struct Game
{
	Board board;
	King king;
	Pawn pawn;
};

#endif
