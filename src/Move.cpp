/*
 * Author: Josue Galeas
 * Last Edit: September 22, 2017
 */

#include "Move.hpp"
#include <cassert>

Move::Move(int *i, int *f)
{
	assert(i);
	assert(f);

	init = new int[2];
	fin = new int[2];

	init[0] = i[0];
	init[1] = i[1];
	fin[0] = f[0];
	fin[1] = f[1];
}
