/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.06
 */

#include "Danger.hpp"
#include "Verification.hpp"
#include <cassert>

char flipColor(char col)
{
	if (col == 'W')
		return 'B';
	else if (col == 'B')
		return 'W';
	else
		return 'E';
}

bool inDanger(int *center, char col, Board *b)
{
	assert(center);
	assert(b);

	std::vector<std::tuple<int, int>> temp;
	return inDangerEnemy(center, col, b, temp);
}

bool inDangerEnemy(int *center, char col, Board *b, std::vector<std::tuple<int, int>> &pos)
{
	assert(center);
	assert(b);
	pos.clear();

	int temp0, temp1, temp2[2];
	char tempColor, tempType;
	char enemyColor = flipColor(col);
	Piece backup, *tempPiece;

	// Looks for kings
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			temp0 = center[0] + i;
			temp1 = center[1] + j;

			if (temp0 < 0 || temp0 > 7)
				continue;
			if (temp1 < 0 || temp1 > 7)
				continue;

			tempColor = b->getPiece(temp0, temp1)->getColor();
			tempType = b->getPiece(temp0, temp1)->getType();

			if (tempColor == enemyColor && tempType == 'K')
				pos.push_back(std::make_tuple(temp0, temp1));
		}
	}

	// Looks for knights
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

			temp0 = center[0] + i;
			temp1 = center[1] + j;

			if (temp0 < 0 || temp0 > 7)
				continue;
			if (temp1 < 0 || temp1 > 7)
				continue;

			tempColor = b->getPiece(temp0, temp1)->getColor();
			tempType = b->getPiece(temp0, temp1)->getType();

			if (tempColor == enemyColor && tempType == 'N')
				pos.push_back(std::make_tuple(temp0, temp1));
		}
	}

	// Looks for everyone else
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			temp0 = center[0];
			temp1 = center[1];

			while (true)
			{
				temp0 += i;
				temp1 += j;

				if (temp0 < 0 || temp0 > 7)
					break;
				if (temp1 < 0 || temp1 > 7)
					break;

				tempColor = b->getPiece(temp0, temp1)->getColor();

				if (tempColor == 'E')
					continue;
				if (tempColor == col)
					break;
				if (tempColor == enemyColor)
				{
					if (b->getPiece(temp0, temp1)->getType() == 'K')
						break;

					temp2[0] = temp0;
					temp2[1] = temp1;
					Move enemyMove(temp2, center);

					// Set dummy piece in the center
					tempPiece = b->getPiece(center);
					backup.setPiece(tempPiece);
					tempPiece->setPiece(col, 'Q', true);

					if (verifyMove(&enemyMove, b))
						pos.push_back(std::make_tuple(temp0, temp1));

					tempPiece->setPiece(&backup);
					break;
				}
			}
		}
	}

	return !pos.empty();
}
