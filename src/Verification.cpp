/*
 * Author: Josue Galeas
 * Last Edit: October 2, 2017
 */

#include "Verification.hpp"
#include "Others.hpp"
#include <cassert>

void updatePieces(Move *m, Game *g)
{
	assert(m);
	assert(g);

	Board *b = &g->board;
	King *k = &g->king;
	Pawn *p = &g->pawn;

	Piece *initPiece = b->getPiece(m->getInit());
	Piece *finPiece = b->getPiece(m->getFin());

	finPiece->setPiece(initPiece);
	initPiece->setPiece('E', 'E', false, " ");

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
		rookInit->setPiece('E', 'E', false, " ");

		k->setCastling();
		k->setRook();
	}

	if (p->getPromo())
	{
		// TODO: Need to ask user what piece they want!
		// However, in almost all cases, they pick queen.
		finPiece->setType('Q');
		b->setSymbol(finPiece);
		p->setPromo();
	}
}

bool verifyCapture(Move *m, Game *g)
{
	assert(m);
	assert(g);

	Board *b = &g->board;
	char initColor = b->getPiece(m->getInit())->getColor();
	char finColor = b->getPiece(m->getFin())->getColor();

	return initColor != finColor;
}

bool verifyMove(Move *m, Game *g)
{
	assert(m);
	assert(g);

	Board *b = &g->board;
	char initType = b->getPiece(m->getInit())->getType();

	switch (initType)
	{
		case 'K':
			return g->king.ifKing(m, b);
		case 'Q':
			return ifQueen(m, b);
		case 'B':
			return ifBishop(m, b);
		case 'N':
			return ifKnight(m, b);
		case 'R':
			return ifRook(m, b);
		case 'P':
			return g->pawn.ifPawn(m, b);
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
