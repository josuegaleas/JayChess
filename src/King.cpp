/*
 * Author: Josue Galeas
 * Last Edit: August 31, 2017
 */

#include "King.hpp"
#include "Checking.hpp"
#include <cassert>

bool ifCastling(int *f, char p, char e, Board *b)
{
	assert(f);
	assert(b);

	if (f[1] == 2)
	{
		bool rook = b->getPiece(f[0], 0)->getMoved();

		if (!rook)
		{
			char knight = b->getPiece(f[0], 1)->getType();
			char bishop = b->getPiece(f[0], 2)->getType();
			char queen = b->getPiece(f[0], 3)->getType();

			if (knight == 'E' && bishop == 'E' && queen == 'E')
			{
				int bishopPos[2] = {f[0], 2};
				int queenPos[2] = {f[0], 3};

				if (!inDanger(bishopPos, p, e, b))
					if (!inDanger(queenPos, p, e, b))
						return true;
			}
		}
	}

	if (f[1] == 6)
	{
		bool rook = b->getPiece(f[0], 7)->getMoved();

		if (!rook)
		{
			char knight = b->getPiece(f[0], 6)->getType();
			char bishop = b->getPiece(f[0], 5)->getType();

			if (knight == 'E' && bishop == 'E')
			{
				int knightPos[2] = {f[0], 6};
				int bishopPos[2] = {f[0], 5};

				if (!inDanger(knightPos, p, e, b))
					if (!inDanger(bishopPos, p, e, b))
						return true;
			}
		}
	}

	return false;
}

bool ifKing(Move *m, Board *b)
{
	assert(m);
	assert(b);

	int *init = m->getInit();
	int *fin = m->getFin();

	int xDiff = abs(fin[0] - init[0]);
	int yDiff = abs(fin[1] - init[1]);

	if (xDiff <= 1 && yDiff <= 1)
		return true;

	if (xDiff == 0 && !b->getPiece(init)->getMoved())
	{
		if (init[0] == 7)
			return ifCastling(fin, 'W', 'B', b);

		if (init[0] == 0)
			return ifCastling(fin, 'B', 'W', b);
	}

	return false;
}
