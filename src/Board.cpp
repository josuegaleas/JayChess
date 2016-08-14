/*
 * Author: Josue Galeas
 * Last Edit: August 13th, 2016
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
