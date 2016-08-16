/*
 * Author: Josue Galeas
 * Last Edit: August 16th, 2016
 */

#include "Game.h"
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

bool Game::verifyMove(char *piece, int *init, int *fin)
{
	bool output = false;

	switch (piece[1])
	{
		case 'K':
			ifKing(piece[0], init, fin);
	}

	return output;
}

void Game::movePiece()
{
	int *init = askLocation();
	char *movingPiece = game.getPiece(init);

	int *fin = askLocation();
	char *stationaryPiece = game.getPiece(fin);

	// TODO: Things to check:
	// If new location has a piece
	// If said piece is enemy piece
	// If current piece is allowed to move to new location
	// Must check if path is clear, etc.

	delete[] init;
	delete[] movingPiece;
	delete[] fin;
	delete[] stationaryPiece;
}
