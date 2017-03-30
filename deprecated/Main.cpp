/*
 * Author: Josue Galeas
 * Last Edit: August 23rd, 2016
 */

#include "Game.hpp"
#include <cstdlib>
using namespace std;

int main()
{
	Game theGame;

	theGame.getBoard().printBoard();

	theGame.movePiece();

	return 0;
}
