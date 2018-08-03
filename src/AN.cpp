/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.24
 */

#include "AN.hpp"
#include "Danger.hpp"
#include "Checkmate.hpp"
#include <cassert>

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
			end += " e.p.";

		if (b->getPawnPromotion())
			end += "Q"; // TODO: Assuming queening

		return capture + end;
	}
}

std::string getANCheck(std::string an, Board *b)
{
	assert(b);

	bool whiteCheckmate = inCheckmate('W', b);
	bool blackCheckmate = inCheckmate('B', b);
	bool whiteCheck = inDanger(b->getKing('W'), 'W', b);
	bool blackCheck = inDanger(b->getKing('B'), 'B', b);

	if (whiteCheckmate || blackCheckmate)
		return an + "#";
	else if (whiteCheck || blackCheck)
		return an + "+";
	else
		return an;
}
