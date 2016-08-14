/*
 * Author: Josue Galeas
 * Last Edit: August 13th, 2016
 */

#include "Board.h"
#include <cstdlib>
#include <iostream>
using namespace std;

void Board::printBoard() const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << board[i][j].getType() << ", ";
		}
		cout << endl;
	}
}
