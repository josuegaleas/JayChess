/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.06
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
	bool output = false;

	switch (initType)
	{
		case 'K':
			output = b->ifKing(m);
			break;
		case 'Q':
			output = ifQueen(m, b);
			break;
		case 'B':
			output = ifBishop(m, b);
			break;
		case 'N':
			output = ifKnight(m, b);
			break;
		case 'R':
			output = ifRook(m, b);
			break;
		case 'P':
			output = b->ifPawn(m);
			break;
		default:
			output = false;
	}

	if (initType != 'P' && output)
		b->setPawnMovedTwo();

	return output;
}
