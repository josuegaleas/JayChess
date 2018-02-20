/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.19
 */

#include "Board.hpp"
#include <cassert>

bool Board::ifPawnHelper(Move *m)
{
	assert(m);

	int *init = m->getInit();
	int *fin = m->getFin();
	bool cond = getPiece(init)->getColor() == 'W';
	char enemy = cond ? 'B':'W';

	if (cond)
	{
		if (fin[0] >= init[0])
			return false;
		if (fin[0] == 0)
			pawnPromotion = true;
	}
	else
	{
		if (fin[0] <= init[0])
			return false;
		if (fin[0] == 7)
			pawnPromotion = true;
	}

	int xDiff = abs(fin[0] - init[0]);
	int yDiff = abs(fin[1] - init[1]);
	char adjColor, finColor = getPiece(fin)->getColor();

	if (getPiece(init)->getMoved())
	{
		if (xDiff > 1 || yDiff > 1)
			return false;
		else
		{
			if (yDiff == 0)
				return finColor == 'E';
			else
				return finColor == enemy;
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
				int o = cond ? -1:1;
				adjColor = getPiece(init[0] + o, init[1])->getColor();
				return adjColor == 'E' && finColor == 'E';
			}
			else
			{
				if (xDiff == 1)
					return finColor == enemy;
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
