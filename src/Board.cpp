/*
 * Author: Josue Galeas
 * Last Edit: September 19, 2017
 */

#include "Board.hpp"
#include <cassert>
#include <cstdio>

void Board::setupPieces(int row)
{
	getPiece(row, 0)->setType('R');
	getPiece(row, 1)->setType('N');
	getPiece(row, 2)->setType('B');
	getPiece(row, 3)->setType('Q');
	getPiece(row, 4)->setType('K');
	getPiece(row, 5)->setType('B');
	getPiece(row, 6)->setType('N');
	getPiece(row, 7)->setType('R');
}

Board::Board()
{
	board = new Piece[64];
	m['P'] = 0;
	m['N'] = 1;
	m['B'] = 2;
	m['R'] = 3;
	m['Q'] = 4;
	m['K'] = 5;

	for (int col = 0; col < 8; col++)
	{
		// Setting top two rows to all black
		getPiece(0, col)->setColor('B');
		getPiece(1, col)->setColor('B');

		// Setting bottom two rows to all white
		getPiece(6, col)->setColor('W');
		getPiece(7, col)->setColor('W');

		// Setting up pawns
		getPiece(1, col)->setType('P');
		getPiece(6, col)->setType('P');
	}

	// Setting up non-pawns
	setupPieces(0);
	setupPieces(7);

	// Setting up symbols
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			setupSymbolOf(getPiece(i, j));
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

void Board::setupSymbolOf(Piece *p)
{
	if (p->getColor() == 'E')
		return;

	std::string symbols[12] =
	{
		"♙", "♘", "♗", "♖", "♕", "♔",
		"♟", "♞", "♝", "♜", "♛", "♚"
	};

	int o = p->getColor() == 'W' ? 0:6;
	p->setSymbol(symbols[m[p->getType()] + o]);
}

void Board::drawBoard() const
{
	char files[] = "|     a   b   c   d   e   f   g   h     |\n";
	char ranks[] = "|   +---+---+---+---+---+---+---+---+   |\n";
	char border[] = "+---------------------------------------+\n";

	printf("%s%s", border, files);

	for (int x = 0; x < 8; x++)
	{
		printf("%s| %d ", ranks, 8 - x);

		for (int y = 0; y < 8; y++)
		{
			printf("| %s ", getPiece(x, y)->getSymbol().c_str());
		}

		printf("| %d |\n", 8 - x);
	}

	printf("%s%s%s", ranks, files, border);
}
