/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.20
 */

#include "Verification.hpp"
#include "VerificationHelper.hpp"
#include <cassert>

void updatePieces(Move *m, Board *b)
{
	assert(m);
	assert(b);

	Piece *initPiece = b->getPiece(m->getInit());
	Piece *finPiece = b->getPiece(m->getFin());

	initPiece->setMoved(true);
	finPiece->setPiece(initPiece);
	initPiece->setPiece('E', 'E', false, " ");

	if (b->getCastling())
	{
		int *rook = b->getRook();
		Piece *rookInit = b->getPiece(rook);
		Piece *rookFin;

		if (rook[2] == 0)
			rookFin = b->getPiece(rook[0], rook[1] + 3);
		else
			rookFin = b->getPiece(rook[0], rook[1] - 2);

		rookInit->setMoved(true);
		rookFin->setPiece(rookInit);
		rookInit->setPiece('E', 'E', false, " ");

		b->setCastling();
		b->setRook();
	}

	if (b->getPawnPromotion())
	{
		// TODO: Need to ask user what piece they want!
		// However, in almost all cases, they pick queen.
		finPiece->setType('Q');
		b->setSymbol(finPiece);
		b->setPawnPromotion();
	}
}

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
