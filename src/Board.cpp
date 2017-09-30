/*
 * Author: Josue Galeas
 * Last Edit: September 29, 2017
 */

#include "Board.hpp"
#include <cassert>

void Board::setMapping()
{
	mapping['P'] = 0;
	mapping['N'] = 1;
	mapping['B'] = 2;
	mapping['R'] = 3;
	mapping['Q'] = 4;
	mapping['K'] = 5;
}

void Board::setPieces(int r)
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
	board = new Piece[64];

	setMapping();
	symbols =
	{
		{"♙", "♘", "♗", "♖", "♕", "♔",
		"♟", "♞", "♝", "♜", "♛", "♚"}
	};

	for (int col = 0; col < 8; col++)
	{
		getPiece(0, col)->setColor('B');
		getPiece(1, col)->setColor('B');

		getPiece(6, col)->setColor('W');
		getPiece(7, col)->setColor('W');

		getPiece(1, col)->setType('P');
		getPiece(6, col)->setType('P');
	}

	setPieces(0);
	setPieces(7);

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			setSymbol(getPiece(i, j));
}

void Board::setSymbol(Piece *p)
{
	if (p->getColor() == 'E')
		return;

	int o = p->getColor() == 'W' ? 0:6;
	int s = mapping[p->getType()] + o;
	p->setSymbol(symbols[s]);
}

Piece *Board::getPiece(int x, int y) const
{
	return board + (x * 8) + y;
}

Piece *Board::getPiece(int *p) const
{
	assert(p);

	return board + (p[0] * 8) + p[1];
}
