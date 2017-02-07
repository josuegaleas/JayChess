/*
 * Author: Josue Galeas
 * Last Edit: Feb 6, 2017
 */

#include "Piece.h"

Piece::Piece()
{
	type = 'E';
	color = 'E';
	moved = false;
	symbol = " ";
}

void Piece::setType(char newType)
{
	type = newType;
}

void Piece::setColor(char newColor)
{
	color = newColor;
}

void Piece::setMoved()
{
	moved = true;
}

void Piece::setSymbol(std::string newSymbol)
{
	symbol = newSymbol;
}
