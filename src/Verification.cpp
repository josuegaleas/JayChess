/*
 * Author: Josue Galeas
 * Last Edit: September 9, 2017
 */

#include "Verification.hpp"
#include "King.hpp"
#include "Pawn.hpp"
#include "Others.hpp"
#include <cassert>

static King k;
static Pawn p;

void updatePieces(Move *m, Board *b)
{
	assert(m);
	assert(b);

	Piece *initPiece = b->getPiece(m->getInit());
	Piece *finPiece = b->getPiece(m->getFin());

	finPiece->setPiece(initPiece);
	initPiece->setPiece('E', 'E', " ");

	if (k.getCastling())
	{
		int *rook = k.getRookPos();
		Piece *rookInit = b->getPiece(rook);
		Piece *rookFin;

		if (rook[2] == 0)
			rookFin = b->getPiece(rook[0], rook[1] + 3);
		else
			rookFin = b->getPiece(rook[0], rook[1] - 2);

		rookFin->setPiece(rookInit);
		rookInit->setPiece('E', 'E', " ");

		k.setCastling();
	}

	if (p.getPromo())
	{
		// TODO: Need to ask user what piece they want!
		// However, in almost all cases, they pick queen.
		finPiece->setType('Q');
		// FIXME: Temporary way to set symbol
		if (finPiece->getColor() == 'W')
			finPiece->setSymbol("♕");
		else
			finPiece->setSymbol("♛");

		p.setPromo();
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
			return k.ifKing(m, b);
		case 'Q':
			return ifQueen(m, b);
		case 'B':
			return ifBishop(m, b);
		case 'N':
			return ifKnight(m, b);
		case 'R':
			return ifRook(m, b);
		case 'P':
			return p.ifPawn(m, b);
		default:
			return false;
	}
}
