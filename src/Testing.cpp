/*
 * Author: Josue Galeas
 * Last Edit: Feb 6, 2016
 */

#include "Board.h"

int main()
{
	Board *b = new Board();

	b->printBoard();
	b->drawBoard();

	delete(b);

	return 0;
}
