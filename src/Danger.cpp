/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.23
 */

#include "Danger.hpp"
#include "Verification.hpp"
#include <cassert>

bool inDanger(int *cen, char col, Board *b)
{
	assert(cen);
	assert(b);

	std::vector<std::tuple<int, int>> temp;
	return inDangerEnemy(cen, col, b, temp);
}

bool inDangerEnemy(int *cen, char col, Board *b, std::vector<std::tuple<int, int>> &pos)
{
	assert(cen);
	assert(b);
	pos.clear();

	int temp0, temp1, temp2[2];
	char color, type;
	bool cond = (col == 'W');
	char enemy = cond ? 'B':'W';
	Piece backup, *T;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			temp0 = cen[0] + i;
			temp1 = cen[1] + j;

			if (temp0 < 0 || temp0 > 7)
				continue;
			if (temp1 < 0 || temp1 > 7)
				continue;

			color = b->getPiece(temp0, temp1)->getColor();
			type = b->getPiece(temp0, temp1)->getType();

			if (color == enemy && type == 'K')
				pos.push_back(std::make_tuple(temp0, temp1));
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

			temp0 = cen[0] + i;
			temp1 = cen[1] + j;

			if (temp0 < 0 || temp0 > 7)
				continue;
			if (temp1 < 0 || temp1 > 7)
				continue;

			color = b->getPiece(temp0, temp1)->getColor();
			type = b->getPiece(temp0, temp1)->getType();

			if (color == enemy && type == 'N')
				pos.push_back(std::make_tuple(temp0, temp1));
		}
	}

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			temp0 = cen[0];
			temp1 = cen[1];

			while (true)
			{
				temp0 += i;
				temp1 += j;

				if (temp0 < 0 || temp0 > 7)
					break;
				if (temp1 < 0 || temp1 > 7)
					break;

				color = b->getPiece(temp0, temp1)->getColor();

				if (color == 'E')
					continue;
				if (color == col)
					break;
				if (color == enemy)
				{
					if (b->getPiece(temp0, temp1)->getType() == 'K')
						break;

					temp2[0] = temp0;
					temp2[1] = temp1;
					Move enemy(temp2, cen);

					T = b->getPiece(cen);
					backup.setPiece(T);
					T->setPiece('Q', col, true, "😂");

					if (verifyMove(&enemy, b))
						pos.push_back(std::make_tuple(temp0, temp1));

					T->setPiece(&backup);
					break;
				}
			}
		}
	}

	return !pos.empty();
}
