/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.08
 */

#include "JNIHelper.hpp"
#include "Danger.hpp"
#include "Checkmate.hpp"
#include <cassert>

void updatePieces(Move *m, Board *b)
{
	assert(m);
	assert(b);

	Piece *initPiece = b->getPiece(m->getInit());
	Piece *finPiece = b->getPiece(m->getFin());

	initPiece->setMoved(true);
	finPiece->setPiece(initPiece);
	initPiece->setPiece('E', 'E', false);

	if (b->getCastling())
	{
		int *rookPos = b->getRook();
		Piece *rookInit = b->getPiece(rookPos);
		Piece *rookFin;

		if (rookPos[1] == 0)
			rookFin = b->getPiece(rookPos[0], 3);
		else if (rookPos[1] == 7)
			rookFin = b->getPiece(rookPos[0], 5);
		else
			return;

		rookInit->setMoved(true);
		rookFin->setPiece(rookInit);
		rookInit->setPiece('E', 'E', false);

		b->setCastling();
		b->setRook();
	}

	if (b->getPawnPromotion())
	{
		// TODO: Need to ask user what piece they want!
		// However, in almost all cases, they pick queen.
		finPiece->setType('Q');
		b->setPawnPromotion();
	}

	if (b->getEnPassant())
	{
		b->setPawnMovedTwo();
		b->setPawn();
		b->setEnPassant();
	}
}

std::string getAN(Move *m, Board *b)
{
	assert(m);
	assert(b);

	if (b->getCastling())
	{
		int *rook = b->getRook();

		if (rook[1] == 0)
			return "0-0-0";
		else if (rook[1] == 7)
			return "0-0";
	}

	int *init = m->getInit();
	int *fin = m->getFin();
	char initAN = 'a';
	char finAN[3] = {'a', '8', '\0'};

	initAN += init[1];
	finAN[0] += fin[1];
	finAN[1] -= fin[0];
	std::string end = std::string(finAN);

	char t = b->getPiece(init)->getType();
	bool c = b->getPiece(fin)->getColor() != 'E';
	std::string capture = c ? "x":"";

	if (t != 'P')
		return std::string(1, t) + capture + end;
	else
	{
		if (c)
			capture = std::string(1, initAN) + capture;

		if (b->getEnPassant())
			end += "e.p.";

		if (b->getPawnPromotion())
			end += "Q"; // TODO: Assuming queening

		return capture + end;
	}
}

void getANCheck(std::string &an, Board *b)
{
	assert(b);

	int *wk = b->getKing('W');
	int *bk = b->getKing('B');

	if (inDanger(wk, 'W', b) || inDanger(bk, 'B', b))
	{
		if (inCheckmate('W', b) || inCheckmate('B', b))
			an += "#";
		else
			an += "+";
	}
}
