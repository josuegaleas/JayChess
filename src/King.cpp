/*
 * Author: Josue Galeas
 * Last Edit: September 19, 2017
 */

#include "King.hpp"
#include "Checking.hpp"
#include <cassert>

bool King::ifCastling(int *f, char p, Board *b)
{
	assert(f);
	assert(b);

	if (f[1] == 2)
	{
		if (!b->getPiece(f[0], 0)->getMoved())
		{
			char knight = b->getPiece(f[0], 1)->getType();
			char bishop = b->getPiece(f[0], 2)->getType();
			char queen = b->getPiece(f[0], 3)->getType();

			if (knight == 'E' && bishop == 'E' && queen == 'E')
			{
				int bishopPos[2] = {f[0], 2};
				int queenPos[2] = {f[0], 3};

				if (!inDanger(bishopPos, p, b))
				{
					if (!inDanger(queenPos, p, b))
					{
						rook[0] = f[0];
						rook[1] = 0;
						rook[2] = 0;
						return castling = true;
					}
				}
			}
		}
	}
	else if (f[1] == 6)
	{
		if (!b->getPiece(f[0], 0)->getMoved())
		{
			char knight = b->getPiece(f[0], 6)->getType();
			char bishop = b->getPiece(f[0], 5)->getType();

			if (knight == 'E' && bishop == 'E')
			{
				int knightPos[2] = {f[0], 6};
				int bishopPos[2] = {f[0], 5};

				if (!inDanger(knightPos, p, b))
				{
					if (!inDanger(bishopPos, p, b))
					{
						rook[0] = f[0];
						rook[1] = 7;
						rook[2] = 1;
						return castling = true;
					}
				}
			}
		}
	}

	return false;
}

bool King::ifKing(Move *m, Board *b)
{
	assert(m);
	assert(b);

	int *init = m->getInit();
	int *fin = m->getFin();
	Piece *player = b->getPiece(init);
	char color = player->getColor();

	int xDiff = abs(fin[0] - init[0]);
	int yDiff = abs(fin[1] - init[1]);

	if (xDiff <= 1 && yDiff <= 1)
		return !inDanger(fin, color, b);
	else if (xDiff == 0 && !player->getMoved())
		return !inDanger(init, color, b) && ifCastling(fin, color, b);

	return false;
}
