/*
 * Author: Josue Galeas
 * Last Edit: September 16, 2017
 */

#include "Verification.hpp"
#include "Others.hpp"
#include <cassert>

void updatePieces(Move *m, Game *g)
{
	assert(m);
	assert(g);

	Board *b = g->getBoard();
	King *k = g->getKing();
	Pawn *p = g->getPawn();
	assert(b);
	assert(k);
	assert(p);

	Piece *initPiece = b->getPiece(m->getInit());
	Piece *finPiece = b->getPiece(m->getFin());

	finPiece->setPiece(initPiece);
	initPiece->setPiece('E', 'E', " ");

	if (k->getCastling())
	{
		int *rook = k->getRook();
		Piece *rookInit = b->getPiece(rook);
		Piece *rookFin;

		if (rook[2] == 0)
			rookFin = b->getPiece(rook[0], rook[1] + 3);
		else
			rookFin = b->getPiece(rook[0], rook[1] - 2);

		rookFin->setPiece(rookInit);
		rookInit->setPiece('E', 'E', " ");

		k->setCastling();
		k->setRook();
	}

	if (p->getPromo())
	{
		// TODO: Need to ask user what piece they want!
		// However, in almost all cases, they pick queen.
		finPiece->setType('Q');
		b->setupSymbolOf(finPiece);
		p->setPromo();
	}
}

bool verifyCapture(Move *m, Game *g)
{
	assert(m);
	assert(g);

	Board *b = g->getBoard();
	assert(b);

	char initColor = b->getPiece(m->getInit())->getColor();
	char finColor = b->getPiece(m->getFin())->getColor();

	return initColor != finColor;
}

bool verifyMove(Move *m, Game *g)
{
	assert(m);
	assert(g);

	Board *b = g->getBoard();
	King *k = g->getKing();
	Pawn *p = g->getPawn();
	assert(b);
	assert(k);
	assert(p);

	char initType = b->getPiece(m->getInit())->getType();

	switch (initType)
	{
		case 'K':
			return k->ifKing(m, b);
		case 'Q':
			return ifQueen(m, b);
		case 'B':
			return ifBishop(m, b);
		case 'N':
			return ifKnight(m, b);
		case 'R':
			return ifRook(m, b);
		case 'P':
			return p->ifPawn(m, b);
		default:
			return false;
	}
}

// FIXME: Need to find a better solution to this
bool verifyMove(Move *m, Board *b)
{
	assert(m);
	assert(b);

	char initType = b->getPiece(m->getInit())->getType();
	King k;
	Pawn p;

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
