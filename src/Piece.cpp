/*
 * Author: Josue Galeas
 * Last Edit: September 22, 2017
 */

#include "Piece.hpp"
#include <cassert>

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

void Piece::setSymbol(std::string newSymbol)
{
	symbol = newSymbol;
}

void Piece::setPiece(char newType, char newColor, bool newMoved, std::string newSymbol)
{
	type = newType;
	color = newColor;
	moved = newMoved;
	symbol = newSymbol;
}

void Piece::setPiece(Piece *newPiece)
{
	assert(newPiece);

	type = newPiece->getType();
	color = newPiece->getColor();
	moved = newPiece->getMoved();
	symbol = newPiece->getSymbol();
}
