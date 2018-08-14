/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.14
 */

#include "Board.hpp"
#include <cassert>

void Board::setColors(int c)
{
	getPiece(0, c)->setColor('B');
	getPiece(1, c)->setColor('B');
	getPiece(6, c)->setColor('W');
	getPiece(7, c)->setColor('W');
}

void Board::setPawns(int c)
{
	getPiece(1, c)->setType('P');
	getPiece(6, c)->setType('P');
}

void Board::setNonPawns(int r)
{
	getPiece(r, 0)->setType('R');
	getPiece(r, 1)->setType('N');
	getPiece(r, 2)->setType('B');
	getPiece(r, 3)->setType('Q');
	getPiece(r, 4)->setType('K');
	getPiece(r, 5)->setType('B');
	getPiece(r, 6)->setType('N');
	getPiece(r, 7)->setType('R');
}

Board::Board()
{
	for (int i = 0; i < 8; i++)
		board[i] = new Piece[8];

	for (int col = 0; col < 8; col++)
	{
		setColors(col);
		setPawns(col);
	}

	setNonPawns(0);
	setNonPawns(7);
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
		delete[] board[i];
	delete[] board;

	// King
	delete[] whiteKingPos;
	delete[] blackKingPos;
	delete[] rookPos;
	delete[] pawnPos;
}

Piece *Board::getPiece(int *p) const
{
	assert(p);

	return getPiece(p[0], p[1]);
}
