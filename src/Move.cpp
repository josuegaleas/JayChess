/*
 * Author: Josue Galeas
 * Last Edit: March 29, 2017
 */

#include "Move.hpp"

Move::Move(int ix, int iy, int fx, int fy)
{
	init = new int[2];
	fin = new int[2];

	init[0] = ix;
	init[1] = iy;
	fin[0] = fx;
	fin[1] = fy;
}

Move::~Move()
{
	delete[] init;
	delete[] fin;
}
