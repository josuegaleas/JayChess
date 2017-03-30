/*
 * Author: Josue Galeas
 * Last Edit: March 29, 2017
 */

#include "Piece.hpp"

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
