/*
 * Author: Josue Galeas
 * Last Edit: August 22nd, 2016
 */

#include "Game.h"
#include <cstdlib>
using namespace std;

int main()
{
	Game game;

	game.getBoard().printBoard();

	game.movePiece();

	return 0;
}
