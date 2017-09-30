/*
 * Author: Josue Galeas
 * Last Edit: September 29, 2017
 */

#include "King.hpp"
#include "Checking.hpp"
#include <cassert>
#include <algorithm>

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

King::King()
{
	castling = false;
	rook = new int[3];
	white = new int[2];
	black = new int[2];

	rook[0] = rook[1] = rook[2] = -1;
	white[0] = 7;
	black[0] = 0;
	white[1] = black[1] = 4;
}

King::~King()
{
	delete[] rook;
	delete[] white;
	delete[] black;
}

void King::setKing(char c, int *p)
{
	assert(p);

	if (c == 'W')
		std::copy(p, p + 2, white);
	else
		std::copy(p, p + 2, black);
}

int *King::getKing(char c) const
{
	if (c == 'W')
		return white;
	else
		return black;
}

bool King::ifKing(Move *m, Board *b)
{
	assert(m);
	assert(b);

	int *init = m->getInit();
	int *fin = m->getFin();
	Piece *piece = b->getPiece(init);
	char color = piece->getColor();
	bool valid = false;

	int xDiff = abs(fin[0] - init[0]);
	int yDiff = abs(fin[1] - init[1]);

	if (xDiff <= 1 && yDiff <= 1)
		valid = !inDanger(fin, color, b);
	else if (xDiff == 0 && !piece->getMoved())
		valid = !inDanger(init, color, b) && ifCastling(fin, color, b);

	if (valid)
		setKing(color, fin);

	return valid;
}
