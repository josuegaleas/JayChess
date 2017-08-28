/*
 * Author: Josue Galeas
 * Last Edit: August 27, 2017
 */

#include "Others.hpp"
#include <cassert>

bool ifQueen(Move *m, Board *b)
{
	assert(m);
	assert(b);

	return ifBishop(m, b) || ifRook(m, b);
}

bool ifBishop(Move *m, Board *b)
{
	assert(m);
	assert(b);

	int *init = m->getInit();
	int *fin = m->getFin();

	int tempX, tempY;

	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			tempX = init[0];
			tempY = init[1];

			while (true)
			{
				tempX += i;
				tempY += j;

				/* Checks if adjacent location is the target */
				if (tempX == fin[0] && tempY == fin[1])
					return true;

				/* Checks if adjacent location is out of bounds */
				if (tempX < 0 || tempX > 7)
					break;
				if (tempY < 0 || tempY > 7)
					break;

				/* Checks if there is a piece blocking the path */
				if (b->getPiece(tempX, tempY)->getType() != 'E')
					break;
			}
		}
	}

	return false;
}

bool ifKnight(Move *m, Board *b)
{
	assert(m);
	assert(b);

	int *init = m->getInit();
	int *fin = m->getFin();

	int tempX, tempY;

	for (int i = -2; i <= 2; i += 4)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			tempX = init[0] + i;
			tempY = init[1] + j;

			if (tempX == fin[0] && tempY == fin[1])
				return true;
		}
	}

	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = -2; j <= 2; j += 4)
		{
			tempX = init[0] + i;
			tempY = init[1] + j;

			if (tempX == fin[0] && tempY == fin[1])
				return true;
		}
	}

	return false;
}

bool ifRook(Move *m, Board *b)
{
	assert(m);
	assert(b);

	int *init = m->getInit();
	int *fin = m->getFin();

	int tempX, tempY;

	if (init[1] == fin[1])
	{
		for (int i = -1; i <= 1; i += 2)
		{
			tempX = init[0];

			while (true)
			{
				tempX += i;

				/* Checks if adjacent location is the target */
				if (tempX == fin[0])
					return true;

				/* Checks if adjacent location is out of bounds */
				if (tempX < 0 || tempX > 7)
					break;

				/* Checks if there is a piece blocking the path */
				if (b->getPiece(tempX, init[1])->getType() != 'E')
					break;
			}
		}
	}

	if (init[0] == fin[0])
	{
		for (int j = -1; j <= 1; j += 2)
		{
			tempY = init[1];

			while (true)
			{
				tempY += j;

				/* Checks if adjacent location is the target */
				if (tempY == fin[1])
					return true;

				/* Checks if adjacent location is out of bounds */
				if (tempY < 0 || tempY > 7)
					break;

				/* Checks if there is a piece blocking the path */
				if (b->getPiece(init[0], tempY)->getType() != 'E')
					break;
			}
		}
	}

	return false;
}
