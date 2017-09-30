/*
 * Author: Josue Galeas
 * Last Edit: September 30, 2017
 */

#include "Others.hpp"
#include <cassert>
#include <algorithm>

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
	int temp[2];

	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			std::copy(init, init + 2, temp);

			while (true)
			{
				temp[0] += i;
				temp[1] += j;

				if (temp[0] == fin[0] && temp[1] == fin[1])
					return true;

				if (temp[0] < 0 || temp[0] > 7)
					break;
				if (temp[1] < 0 || temp[1] > 7)
					break;

				if (b->getPiece(temp)->getType() != 'E')
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
	int temp[2];

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

			temp[0] = init[0] + i;
			temp[1] = init[1] + j;

			if (temp[0] == fin[0] && temp[1] == fin[1])
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
	int temp[2], o;

	if (init[1] == fin[1])
	{
		temp[1] = init[1];
		o = 0;
	}
	else if (init[0] == fin[0])
	{
		temp[0] = init[0];
		o = 1;
	}
	else
		return false;

	for (int i = -1; i <= 1; i += 2)
	{
		temp[o] = init[o];

		while (true)
		{
			temp[o] += i;

			if (temp[o] == fin[o])
				return true;

			if (temp[o] < 0 || temp[o] > 7)
				break;

			if (b->getPiece(temp)->getType() != 'E')
				break;
		}
	}

	return false;
}
