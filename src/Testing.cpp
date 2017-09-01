/*
 * Author: Josue Galeas
 * Last Edit: August 31, 2017
 */

#include "Board.hpp"

int main()
{
	Board *b = new Board();

	b->printBoard();
	b->drawBoard();

	delete b;

	return 0;
}
