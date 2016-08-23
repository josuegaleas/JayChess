/*
 * Author: Josue Galeas
 * Last Edit: August 23rd, 2016
 */

#include "Verification.h"
#include "ActivePiece.h"
#include "Board.h"
#include <cstdlib>
#include <cmath>
using namespace std;

bool ifKing(ActivePiece *init, ActivePiece *fin)
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

bool ifQueen(ActivePiece *init, ActivePiece *fin)
{
	int *from = init->arrayLocation;
	int *to = fin->arrayLocation;

	return false;
}

bool ifBishop(ActivePiece *init, ActivePiece *fin, Board *chessGame)
{
	int *from = init->arrayLocation;
	int *to = fin->arrayLocation;
	int tempX, tempY;

	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			tempX = from[0];
			tempY = from[1];

			while (true)
			{
				tempX += i;
				tempY += j;

				// Checks if adjacent location is the target
				if (tempX == to[0] && tempY == to[1])
					return true;

				// Checks if there is a piece blocking the path
				if (chessGame->getChessPiece(tempX, tempY)->getType() != 'E')
					break;

				// Checks if adjacent location is out of bounds
				if (tempX < 0 || tempX > 7)
					break;
				if (tempY < 0 || tempY > 7)
					break;
			}
		}
	}

	return false;
}
