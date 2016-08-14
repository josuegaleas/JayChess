/*
 * Author: Josue Galeas
 * Last Edit: August 13th, 2016
 */

#include "ChessPiece.h"
#include <cstdlib>
using namespace std;

ChessPiece::ChessPiece()
{
	pieceType = 'E';
}

void ChessPiece::setType(char type)
{
	pieceType = type;
}
