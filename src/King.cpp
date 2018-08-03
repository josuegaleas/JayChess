/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.02
 */

#include "Board.hpp"
#include "Danger.hpp"
#include <cassert>

bool Board::ifCastling(int *fin, char col)
{
	assert(fin);

	if (fin[1] == 2)
	{
		// Queenside
		if (!getPiece(fin[0], 0)->getMoved())
		{
			char knight = getPiece(fin[0], 1)->getType();
			char bishop = getPiece(fin[0], 2)->getType();
			char queen = getPiece(fin[0], 3)->getType();

			if (knight == 'E' && bishop == 'E' && queen == 'E')
			{
				int bishopPos[2] = {fin[0], 2};
				int queenPos[2] = {fin[0], 3};

				if (!inDanger(bishopPos, col, this))
				{
					if (!inDanger(queenPos, col, this))
					{
						rookPos[0] = fin[0];
						rookPos[1] = 0;
						return castling = true;
					}
				}
			}
		}
	}
	else if (fin[1] == 6)
	{
		// Kingside
		if (!getPiece(fin[0], 7)->getMoved())
		{
			char bishop = getPiece(fin[0], 5)->getType();
			char knight = getPiece(fin[0], 6)->getType();

			if (bishop == 'E' && knight == 'E')
			{
				int bishopPos[2] = {fin[0], 5};
				int knightPos[2] = {fin[0], 6};

				if (!inDanger(bishopPos, col, this))
				{
					if (!inDanger(knightPos, col, this))
					{
						rookPos[0] = fin[0];
						rookPos[1] = 7;
						return castling = true;
					}
				}
			}
		}
	}

	return false;
}

void Board::setKing(char col, int *pos)
{
	assert(pos);

	if (col == 'W')
	{
		whiteKingPos[0] = pos[0];
		whiteKingPos[1] = pos[1];
	}
	else if (col == 'B')
	{
		blackKingPos[0] = pos[0];
		blackKingPos[1] = pos[1];
	}
}

int *Board::getKing(char col) const
{
	if (col == 'W')
		return whiteKingPos;
	else if (col == 'B')
		return blackKingPos;
	else
		return nullptr;
}

bool Board::ifKing(Move *m)
{
	assert(m);

	int *init = m->getInit();
	int *fin = m->getFin();
	Piece *king = getPiece(init);
	char color = king->getColor();
	bool valid = false;

	int xDiff = abs(fin[0] - init[0]);
	int yDiff = abs(fin[1] - init[1]);

	if (xDiff <= 1 && yDiff <= 1)
		valid = !inDanger(fin, color, this);
	else if (xDiff == 0 && !king->getMoved())
		valid = !inDanger(init, color, this) && ifCastling(fin, color);

	if (valid)
		setKing(color, fin);

	return valid;
}
