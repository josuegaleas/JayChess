/*
 * Author: Josue Galeas
 * Last Edit: August 28, 2017
 */

#include "Movement.hpp"
#include <cassert>

void updatePieces(Move *m, Board *b)
{
	assert(m);
	assert(b);

	Piece *initPiece = b->getPiece(m->getInit());
	Piece *finPiece = b->getPiece(m->getFin());

	finPiece->setPiece(initPiece);
	initPiece->setPiece('E', 'E', " ");
}
