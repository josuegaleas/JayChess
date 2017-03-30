/*
 * Author: Josue Galeas
 * Last Edit: August 24th, 2016
 */

#include "Game.hpp"
#include "ActivePiece.h"
#include "Verification.h"
#include <cstdlib>
#include <cstdio>
using namespace std;

int *Game::askLocation()
{
	int *output = new int[2];

	while (true)
	{
		printf("x? ");
		scanf("%d", &output[0]);

		if (output[0] >= 0 && output[0] <= 7)
			break;
		else
			printf("ERROR: x is out of bounds, try again.\n");
	}

	while (true)
	{
		printf("y? ");
		scanf("%d", &output[1]);

		if (output[1] >= 0 && output[1] <= 7)
			break;
		else
			printf("ERROR: y is out of bounds, try again.\n");
	}

	return output;
}

bool Game::verifyMove(ActivePiece *init, ActivePiece *fin)
{
	switch (init->piece->getType())
	{
		case 'K':
			return ifKing(init, fin);
		case 'Q':
			return ifQueen(init, fin, &chessBoard);
		case 'B':
			return ifBishop(init, fin, &chessBoard);
		case 'N':
			return ifKnight(init, fin);
		case 'R':
			return ifRook(init, fin, &chessBoard);
		case 'P':
			return ifPawn(init, fin);
		default:
			return false;
	}
}

bool Game::verifyCapture(ActivePiece *init, ActivePiece *fin)
{
	char initColor = init->piece->getColor();
	char finColor = fin->piece->getColor();

	if (initColor != finColor)
		return true;
	else
		return false;
}

void Game::movePiece()
{
	ActivePiece *initialPiece = chessBoard.getActivePiece(askLocation());
	ActivePiece *finalPiece = chessBoard.getActivePiece(askLocation());
	bool validCapture, validMove;

	validCapture = verifyCapture(initialPiece, finalPiece);

	if (validCapture)
	{
		validMove = verifyMove(initialPiece, finalPiece);

		if (validMove)
		{
			finalPiece->piece->setType(initialPiece->piece->getType());
			finalPiece->piece->setColor(initialPiece->piece->getColor());
		}
	}

	// TODO: DEBUG
	printf("Valid move? %d\n", validMove);
	printf("Valid capture? %d\n", validCapture);

	delete initialPiece;
	delete finalPiece;
}
