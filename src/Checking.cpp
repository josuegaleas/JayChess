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

			temp[0] = c[0] + i;
			temp[1] = c[1] + j;

			if (temp[0] < 0 || temp[0] > 7)
				continue;
			if (temp[1] < 0 || temp[1] > 7)
				continue;

			color = b->getPiece(temp)->getColor();
			type = b->getPiece(temp)->getType();

			if (color == e && type == 'N')
				return true;
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

bool inCheckmate(King *k, char p, Board *b)
{
	int temp[2], *king = k->getKing(p);
	bool output = inDanger(king, p, b);

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			temp[0] = king[0] + i;
			temp[1] = king[1] + j;

			if (temp[0] < 0 || temp[0] > 7)
				continue;
			if (temp[1] < 0 || temp[1] > 7)
				continue;

			if (b->getPiece(temp)->getColor() == p)
				continue;

			Move m(king, temp);

			if (verifyMove(&m, b))
				output &= inDanger(temp, p, b);
		}
	}

	// FIXME: Might prematurely end the game!
	// Should also consider being able to take out
	// the enemy or being able to block the path.
	// Might be able to use inDanger to find a fellow
	// piece that can block a checkmate?
	return output;
}
