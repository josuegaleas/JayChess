/*
 * Author: Josue Galeas
 * Last Edit: August 26th, 2016
 */

#include "Board.h"
#include "ActivePiece.h"
#include "ChessPiece.h"
#include <cstdlib>
#include <cstdio>
using namespace std;

void Board::setupPieces(int row)
{
	board[row][0].setType('R');
	board[row][1].setType('N');
	board[row][2].setType('B');
	board[row][3].setType('Q');
	board[row][4].setType('K');
	board[row][5].setType('B');
	board[row][6].setType('N');
	board[row][7].setType('R');
}

Board::Board()
{
	for (int col = 0; col < 8; col++)
	{
		// Setting top two rows to all black
		board[0][col].setColor('B');
		board[1][col].setColor('B');

		// Setting bottom two rows to all white
		board[6][col].setColor('W');
		board[7][col].setColor('W');

		// Setting up pawns
		board[1][col].setType('P');
		board[6][col].setType('P');
	}

	// Setting up non-pawns
	setupPieces(0);
	setupPieces(7);
}

ActivePiece *Board::getActivePiece(int *location)
{
	ActivePiece *output = new ActivePiece;

	int x = location[0];
	int y = location[1];

	output->piece = &board[x][y];
	output->arrayLocation[0] = x;
	output->arrayLocation[1] = y;
	output->gameLocation[0] = y + 'a';
	output->gameLocation[1] = '8' - x;

	// TODO: DEBUG
	printf("%c%c at ", output->piece->getColor(), output->piece->getType());
	printf("%c%c\n", output->gameLocation[0], output->gameLocation[1]);

	delete[] location;
	return output;
}

ChessPiece *Board::getChessPiece(int x, int y)
{
	return &board[x][y];
}

// TODO: DEBUG
void Board::printBoard() const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("%c", board[i][j].getColor());
			printf("%c, ", board[i][j].getType());
		}
		printf("\n");
	}
}
