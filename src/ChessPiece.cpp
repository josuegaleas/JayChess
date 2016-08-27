/*
 * Author: Josue Galeas
 * Last Edit: August 26th, 2016
 */

#include "ChessPiece.h"
#include <cstdlib>
using namespace std;

ChessPiece::ChessPiece()
{
	type = 'E';
	color = 'E';
}

void ChessPiece::setType(char newType)
{
	type = newType;
}

void ChessPiece::setColor(char newColor)
{
	color = newColor;
}
