/*
 * Author: Josue Galeas
 * Last Edit: September 22, 2017
 */

#include "Checking.hpp"
#include "Verification.hpp"
#include <cassert>

bool inDanger(int *c, char p, Board *b)
{
	assert(c);
	assert(b);

	int enemy[2] = {-1, -1};
	return inDangerEnemy(c, p, b, enemy);
}

bool setEnemy(int *e, int *t)
{
	assert(e);
	assert(t);

	e[0] = t[0];
	e[1] = t[1];
	return true;
}

bool inDangerEnemy(int *c, char p, Board *b, int *pos)
{
	assert(c);
	assert(b);
	assert(pos);

	int temp[2];
	char color, type;
	char e = p == 'W' ? 'B':'W';

	/* This for-loop looks for kings */
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			temp[0] = c[0] + i;
			temp[1] = c[1] + j;

			if (temp[0] < 0 || temp[0] > 7)
				continue;
			if (temp[1] < 0 || temp[1] > 7)
				continue;

			color = b->getPiece(temp)->getColor();
			type = b->getPiece(temp)->getType();

			if (color == e && type == 'K')
				return setEnemy(pos, temp);
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

			temp[0] = c[0] + i;
			temp[1] = c[1] + j;

			if (temp[0] < 0 || temp[0] > 7)
				continue;
			if (temp[1] < 0 || temp[1] > 7)
				continue;

			color = b->getPiece(temp)->getColor();
			type = b->getPiece(temp)->getType();

			if (color == e && type == 'N')
				return setEnemy(pos, temp);
		}
	}

	/* This for-loop looks for everything else */
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			temp[0] = c[0];
			temp[1] = c[1];

			while (true)
			{
				temp[0] += i;
				temp[1] += j;

				if (temp[0] < 0 || temp[0] > 7)
					break;
				if (temp[1] < 0 || temp[1] > 7)
					break;

				color = b->getPiece(temp)->getColor();

				if (color == 'E')
					continue;
				if (color == p)
					break;
				if (color == e)
				{
					Move enemy(temp, c);

					if (b->getPiece(temp)->getType() == 'P')
					{
						Piece backup;
						backup.setPiece(b->getPiece(c));
						b->getPiece(c)->setPiece('Q', p, true, "😂");

						if (verifyMove(&enemy, b))
						{
							b->getPiece(c)->setPiece(&backup);
							return setEnemy(pos, temp);
						}

						b->getPiece(c)->setPiece(&backup);
						break;
					}

					if (verifyMove(&enemy, b))
						return setEnemy(pos, temp);
					break;
				}
			}
		}
	}

	pos[0] = pos[1] = -1;
	return false;
}
