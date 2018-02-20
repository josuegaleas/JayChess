/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.20
 */

#include "Danger.hpp"
#include "Verification.hpp"
#include <cassert>

bool inDanger(int *cen, char col, Board *b)
{
	assert(cen);
	assert(b);

	std::vector<std::tuple<int, int>> enemy;
	return inDangerEnemy(cen, col, b, enemy);
}

bool inDangerEnemy(int *cen, char col, Board *b, std::vector<std::tuple<int, int>> &pos)
{
	assert(cen);
	assert(b);
	pos.clear();

	int temp[2];
	char color, type;
	bool cond = col == 'W';
	char e = cond ? 'B':'W';

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			temp[0] = cen[0] + i;
			temp[1] = cen[1] + j;

			if (temp[0] < 0 || temp[0] > 7)
				continue;
			if (temp[1] < 0 || temp[1] > 7)
				continue;

			color = b->getPiece(temp)->getColor();
			type = b->getPiece(temp)->getType();

			if (color == e && type == 'K')
				pos.push_back(std::make_tuple(temp[0], temp[1]));
		}
	}

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

			temp[0] = cen[0] + i;
			temp[1] = cen[1] + j;

			if (temp[0] < 0 || temp[0] > 7)
				continue;
			if (temp[1] < 0 || temp[1] > 7)
				continue;

			color = b->getPiece(temp)->getColor();
			type = b->getPiece(temp)->getType();

			if (color == e && type == 'N')
				pos.push_back(std::make_tuple(temp[0], temp[1]));
		}
	}

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			temp[0] = cen[0];
			temp[1] = cen[1];

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
				if (color == col)
					break;
				if (color == e)
				{
					Move enemy(temp, cen);

					// TODO: Does this only have to be done with pawns? Can't remember
					if (b->getPiece(temp)->getType() == 'P')
					{
						Piece backup;
						backup.setPiece(b->getPiece(cen));
						b->getPiece(cen)->setPiece('Q', col, true, "😂");

						if (verifyMove(&enemy, b))
							pos.push_back(std::make_tuple(temp[0], temp[1]));

						b->getPiece(cen)->setPiece(&backup);
						break;
					}

					if (verifyMove(&enemy, b))
						pos.push_back(std::make_tuple(temp[0], temp[1]));
					break;
				}
			}
		}
	}

	return !pos.empty();
}
