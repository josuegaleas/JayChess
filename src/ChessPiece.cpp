/*
 * Author: Josue Galeas
 * Last Edit: August 16th, 2016
 */

#include "ChessPiece.h"
#include <cstdlib>
using namespace std;

ChessPiece::ChessPiece()
{
	type = 'E';
	color = 'E';
	tile = 'E';
}

void ChessPiece::setType(char newType)
{
	type = newType;
}

void ChessPiece::setColor(char newColor)
{
	color = newColor;
}

void ChessPiece::setTile(char newTile)
{
	tile = newTile;
}
