/*
 * Author: Josue Galeas
 * Last Edit: August 27, 2017
 */

#include "Pawn.hpp"
#include "Piece.hpp"
#include <cassert>

bool ifWhitePawn(Move *m, Board *b)
{
	assert(m);
	assert(b);

	int *init = m->getInit();
	int *fin = m->getFin();

	if (fin[0] >= init[0])
		return false;

	Piece *initPiece = b->getPiece(init);
	Piece *finPiece = b->getPiece(fin);

	int xDiff = abs(fin[0] - init[0]);
	int yDiff = abs(fin[1] - init[1]);

	if (initPiece->getMoved())
	{
		if (xDiff > 1 || yDiff > 1)
			return false;
		else
		{
			if (yDiff == 0)
				return finPiece->getColor() == 'E';
			else
				return finPiece->getColor() == 'B';
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
				Piece *abovePiece = b->getPiece(init[0] - 1, init[1]);
				return abovePiece->getColor() == 'E' && finPiece->getColor() == 'E';
			}
			else
			{
				if (xDiff == 1)
					return finPiece->getColor() == 'B';
				else
					return false;
			}
		}
	}
}

bool ifBlackPawn(Move *m, Board *b)
{
	assert(m);
	assert(b);

	int *init = m->getInit();
	int *fin = m->getFin();

	if (fin[0] <= init[0])
		return false;

	Piece *initPiece = b->getPiece(init);
	Piece *finPiece = b->getPiece(fin);

	int xDiff = abs(fin[0] - init[0]);
	int yDiff = abs(fin[1] - init[1]);

	if (initPiece->getMoved())
	{
		if (xDiff > 1 || yDiff > 1)
			return false;
		else
		{
			if (yDiff == 0)
				return finPiece->getColor() == 'E';
			else
				return finPiece->getColor() == 'W';
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
				Piece *belowPiece = b->getPiece(init[0] + 1, init[1]);
				return belowPiece->getColor() == 'E' && finPiece->getColor() == 'E';
			}
			else
			{
				if (xDiff == 1)
					return finPiece->getColor() == 'W';
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

	switch (initColor)
	{
		case 'W':
			return ifWhitePawn(m, b);
		case 'B':
			return ifBlackPawn(m, b);
		default:
			return false;
	}
}
