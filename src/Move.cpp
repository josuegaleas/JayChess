/*
 * Author: Josue Galeas
 * Last Edit: October 2, 2017
 */

#include "Move.hpp"
#include <cassert>
#include <algorithm>

Move::Move(int *i, int *f)
{
	assert(i);
	assert(f);

	std::copy(i, i + 2, init = new int[2]);
	std::copy(f, f + 2, fin = new int[2]);
}
