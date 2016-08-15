/*
 * Author: Josue Galeas
 * Last Edit: August 15th, 2016
 */

#include "Board.h"
#include <cstdlib>
#include <iostream>
using namespace std;

void Board::setPieces(int row)
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
	setPieces(0);
	setPieces(7);
}

char *Board::getPiece(int x, int y)
{
	char *output = new char[4];

	// TODO: Bound checking for inputs

	output[0] = board[x][y].getColor();
	output[1] = board[x][y].getType();
	output[2] = y + 97;
	output[3] = '8' - x;

	// TODO: DEBUG
	cout << output[0] << output[1] << " at ";
	cout << output[2] << output[3] << endl;

	return output;
}

void Board::movePiece()
{
	int xi, yi, xf, yf;

	cout << "x initial? ";
	cin >> xi;
	cout << "y initial? ";
	cin >> yi;

	char *movingPiece = getPiece(xi, yi);

	cout << "x final? ";
	cin >> xf;
	cout << "y final? ";
	cin >> yf;

	char *newLocation = getPiece(xf, yf);

	// TODO: Things to check:
	// If new location has a piece
	// If said piece is enemy piece
	// If current piece is allowed to move to new location
	// Must check if path is clear, etc.

	delete[] movingPiece;
	delete[] newLocation;
}

void Board::printBoard() const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << board[i][j].getColor();
			cout << board[i][j].getType() << ", ";
		}
		cout << endl;
	}
}
