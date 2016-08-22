/*
 * Author: Josue Galeas
 * Last Edit: August 22nd, 2016
 */

#include "Verification.h"
#include "MovingPiece.h"
#include <cstdlib>
#include <cmath>
using namespace std;

bool ifKing(MovingPiece *init, MovingPiece *fin)
{
	int *from = init->arrayLocation;
	int *to = fin->arrayLocation;

	int xDiff = abs(to[0] - from[0]);
	int yDiff = abs(to[1] - from[1]);

	if (xDiff <= 1 && yDiff <= 1)
		return true;
	else
		return false;
}

bool ifQueen(MovingPiece *init, MovingPiece *fin)
{
	int *from = init->arrayLocation;
	int *to = fin->arrayLocation;

	return false;
}
