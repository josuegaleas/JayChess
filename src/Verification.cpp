/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.02
 */

#include "Verification.hpp"
#include "VerificationHelper.hpp"
#include <cassert>

bool verifyCapture(Move *m, Board *b)
{
	assert(m);
	assert(b);

	char initColor = b->getPiece(m->getInit())->getColor();
	char finColor = b->getPiece(m->getFin())->getColor();

	return initColor != finColor;
}

bool verifyMove(Move *m, Board *b)
{
	assert(m);
	assert(b);

	char initType = b->getPiece(m->getInit())->getType();

	switch (initType)
	{
		case 'K':
			return b->ifKing(m);
		case 'Q':
			return ifQueen(m, b);
		case 'B':
			return ifBishop(m, b);
		case 'N':
			return ifKnight(m, b);
		case 'R':
			return ifRook(m, b);
		case 'P':
			return b->ifPawn(m);
		default:
			return false;
	}
}
