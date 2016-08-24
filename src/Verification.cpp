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

bool ifQueen(ActivePiece *init, ActivePiece *fin, Board *chessGame)
{
	return ifBishop(init, fin, chessGame) || ifRook(init, fin, chessGame);
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

				// Checks if adjacent location is out of bounds
				if (tempX < 0 || tempX > 7)
					break;
				if (tempY < 0 || tempY > 7)
					break;

				// Checks if there is a piece blocking the path
				if (chessGame->getChessPiece(tempX, tempY)->getType() != 'E')
					break;
			}
		}
	}

	return false;
}

bool ifKnight(ActivePiece *init, ActivePiece *fin)
{
	return false;
}

bool ifRook(ActivePiece *init, ActivePiece *fin, Board *chessGame)
{
	int *from = init->arrayLocation;
	int *to = fin->arrayLocation;
	int tempX, tempY;

	if (from[0] != to[0] && from[1] != to[1])
		return false;

	for (int i = -1; i <= 1; i += 2)
	{
		tempX = from[0];

		while (true)
		{
			tempX += i;

			// Checks if adjacent location is the target
			if (tempX == to[0] && from[1] == to[1])
				return true;

			// Checks if adjacent location is out of bounds
			if (tempX < 0 || tempX > 7)
				break;

			// Checks if there is a piece blocking the path
			if (chessGame->getChessPiece(tempX, from[1])->getType() != 'E')
				break;
		}
	}

	for (int j = -1; j <= 1; j += 2)
	{
		tempY = from[1];

		while (true)
		{
			tempY += j;

			// Checks if adjacent location is the target
			if (from[0] == to[0] && tempY == to[1])
				return true;

			// Checks if adjacent location is out of bounds
			if (tempY < 0 || tempY > 7)
				break;

			// Checks if there is a piece blocking the path
			if (chessGame->getChessPiece(from[0], tempY)->getType() != 'E')
				break;
		}
	}

	return false;
}

bool ifPawn(ActivePiece *init, ActivePiece *fin)
{
	return false;
}
