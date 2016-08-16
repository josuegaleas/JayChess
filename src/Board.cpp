/*
 * Author: Josue Galeas
 * Last Edit: August 16th, 2016
 */

#include "Board.h"
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

	// Setting up tile colors
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (row % 2 == 0)
			{
				if (col % 2 == 0)
					board[row][col].setTile('L');
				else
					board[row][col].setTile('D');
			}
			else
			{
				if (col % 2 != 0)
					board[row][col].setTile('L');
				else
					board[row][col].setTile('D');
			}
		}
	}
}

char *Board::getPiece(int *location)
{
	char *output = new char[4];
	int x = location[0];
	int y = location[1];

	output[0] = board[x][y].getColor();
	output[1] = board[x][y].getType();
	output[2] = y + 'a';
	output[3] = '8' - x;

	// TODO: DEBUG
	printf("%c%c at ", output[0], output[1]);
	printf("%c%c\n", output[2], output[3]);

	return output;
}

void Board::printBoard() const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("%c", board[i][j].getColor());
			printf("%c", board[i][j].getType());
			printf("%c, ", board[i][j].getTile());
		}
		printf("\n");
	}
}
