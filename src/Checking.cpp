/*
 * Author: Josue Galeas
 * Last Edit: September 19, 2017
 */

#include "Checking.hpp"
#include "Verification.hpp"
#include <cassert>

bool inDanger(int *c, char p, Board *b)
{
	assert(c);
	assert(b);

	int tempX, tempY;
	char color, type;
	char e = p == 'W' ? 'B':'W';

	/* This for-loop looks for kings */
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			tempX = c[0] + i;
			tempY = c[1] + j;

			if (tempX < 0 || tempX > 7)
				continue;
			if (tempY < 0 || tempY > 7)
				continue;

			color = b->getPiece(tempX, tempY)->getColor();
			type = b->getPiece(tempX, tempY)->getType();

			if (color == e && type == 'K')
				return true;
		}
	}

	/* This for-loop looks for knights */
	for (int i = -2; i <= 2; i++)
	{
		if (i == 0)
			continue;

		for (int j = -2; j <= 2; j++)
		{
			if (j == 0)
				continue;
			if (abs(i) == abs(j))
				continue;

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
					Move enemy(tempX, tempY, c[0], c[1]);

					if (b->getPiece(tempX, tempY)->getType() == 'P')
					{
						Piece backup;
						backup.setPiece(b->getPiece(c));
						b->getPiece(c)->setPiece('Q', p, "T");

						if (verifyMove(&enemy, b))
						{
							b->getPiece(c)->setPiece(&backup);
							return true;
						}

						b->getPiece(c)->setPiece(&backup);
						break;
					}

					if (verifyMove(&enemy, b))
						return true;
					break;
				}
			}
		}
	}

	return false;
}
