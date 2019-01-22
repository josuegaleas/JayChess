/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.14
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
		int *rookPos = b->getRookPos();
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
		b->setRookPos();
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
		b->setPawnPos();
		b->setEnPassant();
	}
}

std::string getAN(Move *m, Board *b)
{
	assert(m);
	assert(b);

	if (b->getCastling())
	{
		int *rookPos = b->getRookPos();

		if (rookPos[1] == 0)
			return "O-O-O";
		else if (rookPos[1] == 7)
			return "O-O";
	}

	int *init = m->getInit();
	int *fin = m->getFin();
	char initAN = 'a';
	char finAN[3] = {'a', '8', '\0'};

	initAN += init[1];
	finAN[0] += fin[1];
	finAN[1] -= fin[0];
	std::string end = std::string(finAN);

	char type = b->getPiece(init)->getType();
	bool capture = b->getPiece(fin)->getColor() != 'E';
	std::string caught = capture ? "x":"";

	if (type != 'P')
		return std::string(1, type) + caught + end;
	else if (type == 'P')
	{
		if (capture)
			caught = std::string(1, initAN) + caught;

		if (b->getEnPassant())
			end += "e.p.";

		if (b->getPawnPromotion())
			end += "Q"; // TODO: Assuming queening

		return caught + end;
	}
	else
		return "ERROR";
}

void getANCheck(std::string &an, Board *b)
{
	assert(b);

	int *wk = b->getKingPos('W');
	int *bk = b->getKingPos('B');

	if (inDanger(wk, 'W', b) || inDanger(bk, 'B', b))
	{
		if (inCheckmate('W', b) || inCheckmate('B', b))
		{
			an += "#";
			b->setCheckmate();
		}
		else
			an += "+";
	}
}
