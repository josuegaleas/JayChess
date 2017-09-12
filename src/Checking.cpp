/*
 * Author: Josue Galeas
 * Last Edit: September 12, 2017
 */

#include "Checking.hpp"
#include "Verification.hpp"
#include <cassert>

bool inDanger(int *c, char p, Board *b)
{
	assert(c);
	assert(b);

	int tempX, tempY;
	char color, type, e = p == 'W' ? 'B':'W';

	/* These for-loops look for knights */
	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = -2; j <= 2; j += 4)
		{
			tempX = c[0] + i;
			tempY = c[1] + j;

			if (tempX < 0 || tempX > 7)
				continue;
			if (tempY < 0 || tempY > 7)
				continue;

			color = b->getPiece(tempX, tempY)->getColor();
			type = b->getPiece(tempX, tempY)->getType();

			if (color == e && type == 'N')
				return true;
		}
	}

	for (int i = -2; i <= 2; i += 4)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			tempX = c[0] + i;
			tempY = c[1] + j;

			if (tempX < 0 || tempX > 7)
				continue;
			if (tempY < 0 || tempY > 7)
				continue;

			color = b->getPiece(tempX, tempY)->getColor();
			type = b->getPiece(tempX, tempY)->getType();

			if (color == e && type == 'N')
				return true;
		}
	}

	/* Diagonal, vertical, and horizontal paths */
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			tempX = c[0];
			tempY = c[1];

			while (true)
			{
				tempX += i;
				tempY += j;

				if (tempX < 0 || tempX > 7)
					break;
				if (tempY < 0 || tempY > 7)
					break;

				color = b->getPiece(tempX, tempY)->getColor();

				if (color == 'E')
					continue;
				if (color == p)
					break;
				if (color == e)
				{
					Move *enemy = new Move(tempX, tempY, c[0], c[1]);

					if (verifyMove(enemy, b))
					{
						delete enemy;
						return true;
					}
					else
					{
						delete enemy;
						break;
					}
				}
			}
		}
	}

	return false;
}
