/*
 * Author: Josue Galeas
 * Last Edit: September 4, 2017
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
