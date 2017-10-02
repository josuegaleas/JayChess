/*
 * Author: Josue Galeas
 * Last Edit: October 2, 2017
 */

#include "Piece.hpp"
#include <cassert>

Piece::Piece()
{
	type = 'E';
	color = 'E';
	moved = false;
	symbol = " ";
}

void Piece::setPiece(char t, char c, bool m, std::string s)
{
	type = t;
	color = c;
	moved = m;
	symbol = s;
}

void Piece::setPiece(Piece *p)
{
	assert(p);

	type = p->getType();
	color = p->getColor();
	moved = p->getMoved();
	symbol = p->getSymbol();
}
