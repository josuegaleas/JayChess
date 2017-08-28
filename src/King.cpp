/*
 * Author: Josue Galeas
 * Last Edit: August 27, 2017
 */

#include "King.hpp"
#include <cassert>

bool ifKing(Move *m, Board *b)
{
	assert(m);
	assert(b);

	int *init = m->getInit();
	int *fin = m->getFin();

	int xDiff = abs(fin[0] - init[0]);
	int yDiff = abs(fin[1] - init[1]);

	return xDiff <= 1 && yDiff <= 1;
}
