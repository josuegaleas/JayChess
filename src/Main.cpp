/*
 * Author: Josue Galeas
 * Last Edit: August 15th, 2016
 */

#include "Board.h"
#include <cstdlib>
using namespace std;

int main()
{
	Board game;

	game.printBoard();

	game.movePiece();

	return 0;
}
