/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.21
 */

#include "Board.hpp"
#include "Danger.hpp"
#include <cassert>

bool Board::ifCastling(int *f, char p)
{
	assert(f);

	// TODO: Should we verify that the Rook is indeed a Rook?

	if (f[1] == 2)
	{
		if (!getPiece(f[0], 0)->getMoved())
		{
			char knight = getPiece(f[0], 1)->getType();
			char bishop = getPiece(f[0], 2)->getType();
			char queen = getPiece(f[0], 3)->getType();

			if (knight == 'E' && bishop == 'E' && queen == 'E')
			{
				int bishopPos[2] = {f[0], 2};
				int queenPos[2] = {f[0], 3};

				if (!inDanger(bishopPos, p, this))
				{
					if (!inDanger(queenPos, p, this))
					{
						rook[0] = f[0];
						rook[1] = rook[2] = 0;
						return castling = true;
					}
				}
			}
		}
	}
	else if (f[1] == 6)
	{
		if (!getPiece(f[0], 7)->getMoved())
		{
			char knight = getPiece(f[0], 6)->getType();
			char bishop = getPiece(f[0], 5)->getType();

			if (knight == 'E' && bishop == 'E')
			{
				int knightPos[2] = {f[0], 6};
				int bishopPos[2] = {f[0], 5};

				if (!inDanger(knightPos, p, this))
				{
					if (!inDanger(bishopPos, p, this))
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

void Board::setKing(char c, int *p)
{
	assert(p);

	if (c == 'W')
	{
		whiteKing[0] = p[0];
		whiteKing[1] = p[1];
	}
	else
	{
		blackKing[0] = p[0];
		blackKing[1] = p[1];
	}
}

int *Board::getKing(char c) const
{
	if (c == 'W')
		return whiteKing;
	else
		return blackKing;
}

bool Board::ifKing(Move *m)
{
	assert(m);

	int *init = m->getInit();
	int *fin = m->getFin();
	Piece *piece = getPiece(init);
	char color = piece->getColor();
	bool valid = false;

	int xDiff = abs(fin[0] - init[0]);
	int yDiff = abs(fin[1] - init[1]);

	if (xDiff <= 1 && yDiff <= 1)
		valid = !inDanger(fin, color, this);
	else if (xDiff == 0 && !piece->getMoved())
		valid = !inDanger(init, color, this) && ifCastling(fin, color);

	// FIXME: If we are only temporary moving the King, this might get updated incorrectly?
	if (valid)
		setKing(color, fin);

	return valid;
}
