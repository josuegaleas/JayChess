/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.08
 */

#include "Board.hpp"
#include <cassert>

bool Board::resetPawnFlags()
{
	pawnMovedTwo = false;
	pawnPos[0] = pawnPos[1] = -1;

	return true;
}

bool Board::ifEnPassant(Move *m, bool isWhite)
{
	assert(m);

	int *fin = m->getFin();
	int enemyPos = isWhite ? 3:4;
	char enemyColor = isWhite ? 'B':'W';

	if (pawnPos[0] != enemyPos)
		return false;
	if (pawnPos[1] != fin[1])
		return false;

	Piece *adjPiece, *finPiece;
	adjPiece = getPiece(enemyPos, fin[1]);

	if (adjPiece->getType() == 'P')
	{
		if (adjPiece->getColor() == enemyColor)
		{
			if (pawnMovedTwo)
			{
				// Moving up/down the captured piece to simplify capture
				finPiece = getPiece(fin);
				finPiece->setPiece(adjPiece);
				adjPiece->setPiece('E', 'E', false);

				return enPassant = true;
			}
		}
	}

	return false;
}

bool Board::ifPawnHelper(Move *m)
{
	assert(m);

	int *init = m->getInit();
	int *fin = m->getFin();
	Piece *initPiece = getPiece(init);

	bool possibleEP = false;
	bool isWhite = initPiece->getColor() == 'W';
	char enemyColor = isWhite ? 'B':'W';


	if (isWhite)
	{
		if (fin[0] >= init[0])
			return false;
		else if (fin[0] == 0)
			pawnPromotion = true;
		else if (init[0] == 3)
			possibleEP = true;
	}
	else
	{
		if (fin[0] <= init[0])
			return false;
		else if (fin[0] == 7)
			pawnPromotion = true;
		else if (init[0] == 4)
			possibleEP = true;
	}

	int xDiff = abs(fin[0] - init[0]);
	int yDiff = abs(fin[1] - init[1]);
	char adjColor, finColor = getPiece(fin)->getColor();

	if (initPiece->getMoved())
	{
		if (xDiff > 1 || yDiff > 1)
			return false;
		else
		{
			if (yDiff == 0)
			{
				if (finColor == 'E')
					return resetPawnFlags();
				else
					return false;
			}
			else
			{
				if (possibleEP && finColor == 'E')
					return ifEnPassant(m, isWhite);
				else
				{
					if (finColor == enemyColor)
						return resetPawnFlags();
					else
						return false;
				}
			}
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
				if (xDiff == 1)
				{
					if (finColor == 'E')
						return resetPawnFlags();
					else
						return false;
				}
				else if (xDiff == 2)
				{
					if (isWhite)
						adjColor = getPiece(init[0] - 1, init[1])->getColor();
					else
						adjColor = getPiece(init[0] + 1, init[1])->getColor();

					if (adjColor == 'E' && finColor == 'E')
					{
						pawnPos[0] = fin[0];
						pawnPos[1] = fin[1];

						return pawnMovedTwo = true;
					}
					else
						return false;
				}
				else
					return false;
			}
			else
			{
				if (xDiff == 1)
				{
					if (finColor == enemyColor)
						return resetPawnFlags();
					else
						return false;
				}
				else
					return false;
			}
		}
	}
}

bool Board::ifPawn(Move *m)
{
	assert(m);

	if (ifPawnHelper(m))
		return true;
	else
		return pawnPromotion = false;
}
