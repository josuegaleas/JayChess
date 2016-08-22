/*
 * Author: Josue Galeas
 * Last Edit: August 22nd, 2016
 */

#include "Game.h"
#include "MovingPiece.h"
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

bool Game::verifyMove(MovingPiece *init, MovingPiece *fin)
{
	switch (init->piece->getType())
	{
		case 'K':
			return ifKing(init, fin);
		case 'Q':
			return ifQueen(init, fin);
		default:
			return false;
	}
}

bool Game::verifyCapture(MovingPiece *init, MovingPiece *fin)
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
	MovingPiece *initialPiece = game.getPiece(askLocation());
	MovingPiece *finalPiece = game.getPiece(askLocation());

	bool validMove = verifyMove(initialPiece, finalPiece);
	bool validCapture = verifyCapture(initialPiece, finalPiece);

	printf("Valid move? %d\n", validMove);
	printf("Valid capture? %d\n", validCapture);

	// TODO: Things to check:
	// If new location has a piece
	// If said piece is enemy piece
	// If current piece is allowed to move to new location
	// Must check if path is clear, etc.

	delete initialPiece;
	delete finalPiece;
}
