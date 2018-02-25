/*
 * Author: Josue Galeas
 * Last Edit: 2017.10.02
 */

#include "Piece.hpp"
#include <cassert>

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
