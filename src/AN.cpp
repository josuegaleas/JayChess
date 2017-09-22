/*
 * Author: Josue Galeas
 * Last Edit: September 22, 2017
 */

#include "AN.hpp"
#include "Checking.hpp"
#include <cassert>

std::string getAN(Move *m, Game *g)
{
	assert(m);
	assert(g);

	Board *b = g->getBoard();
	King *k = g->getKing();
	Pawn *p = g->getPawn();
	assert(b);
	assert(k);
	assert(p);

	if (k->getCastling())
	{
		int *rook = k->getRook();

		if (rook[1] == 0)
			return "0-0-0";
		if (rook[1] == 7)
			return "0-0";
	}

	int *init = m->getInit();
	int *fin = m->getFin();
	char initAN = 'a' + init[1];
	char finAN[3] = {'a', '8', '\0'};
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

		if (p->getPassant())
			end += " e.p.";

		if (p->getPromo())
			end += "Q"; // FIXME: Assuming queening

		return capture + end;
	}

	return "UNDEF";
}

std::string getANCheck(std::string an, Game *g)
{
	assert(g);

	Board *b = g->getBoard();
	King *k = g->getKing();
	assert(b);
	assert(k);

	bool whiteCheckmate = inCheckmate(k, 'W', b);
	bool blackCheckmate = inCheckmate(k, 'B', b);
	bool whiteCheck = inDanger(k->getKing('W'), 'W', b);
	bool blackCheck = inDanger(k->getKing('B'), 'B', b);

	if (whiteCheckmate || blackCheckmate)
		return an + "#";
	else if (whiteCheck || blackCheck)
		return an + "+";

	return an;
}
