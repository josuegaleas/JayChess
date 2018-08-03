/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.02
 */

#include "Piece.hpp"
#include <cassert>

void Piece::setPiece(char c, char t, bool m)
{
	color = c;
	type = t;
	moved = m;
}

void Piece::setPiece(Piece *p)
{
	assert(p);

	color = p->getColor();
	type = p->getType();
	moved = p->getMoved();
}
