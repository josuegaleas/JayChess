/*
 * Author: Josue Galeas
 * Last Edit: September 8, 2017
 */

#include "Pawn.hpp"
#include "Piece.hpp"
#include <cassert>

bool ifPawnHelper(Move *m, char p, Board *b)
{
	assert(m);
	assert(b);

	int *init = m->getInit();
	int *fin = m->getFin();
	bool cond = p == 'W';
	char e;

	if (cond)
	{
		if (fin[0] >= init[0])
			return false;
		e = 'B';
	}
	else
	{
		if (fin[0] <= init[0])
			return false;
		e = 'W';
	}

	int xDiff = abs(fin[0] - init[0]);
	int yDiff = abs(fin[1] - init[1]);
	char finColor = b->getPiece(fin)->getColor(), adjColor;

	if (b->getPiece(init)->getMoved())
	{
		if (xDiff > 1 || yDiff > 1)
			return false;
		else
		{
			if (yDiff == 0)
				return finColor == 'E';
			else
				return finColor == e;
		}
	}
	else
	{
		if (xDiff > 2 || yDiff > 1)
			return false;
		else
		{
			if (yDiff == 0)
			{
				if (cond)
					adjColor = b->getPiece(init[0] - 1, init[1])->getColor();
				else
					adjColor = b->getPiece(init[0] + 1, init[1])->getColor();
				return adjColor == 'E' && finColor == 'E';
			}
			else
			{
				if (xDiff == 1)
					return finColor == e;
				else
					return false;
			}
		}
	}
}

bool ifPawn(Move *m, Board *b)
{
	assert(m);
	assert(b);

	char initColor = b->getPiece(m->getInit())->getColor();
	return ifPawnHelper(m, initColor, b);
}
