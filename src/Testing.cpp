/*
 * Author: Josue Galeas
 * Last Edit: March 29, 2016
 */

#include "Board.hpp"

int main()
{
	Board *b = new Board();

	b->printBoard();
	b->drawBoard();

	delete(b);

	return 0;
}
