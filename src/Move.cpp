/*
 * Author: Josue Galeas
 * Last Edit: September 9, 2017
 */

#include "Move.hpp"
#include <cassert>

Move::Move(int ix, int iy, int fx, int fy)
{
	init = new int[2];
	fin = new int[2];

	init[0] = ix;
	init[1] = iy;
	fin[0] = fx;
	fin[1] = fy;
}
