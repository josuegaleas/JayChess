/*
 * Author: Josue Galeas
 * Last Edit: August 23rd, 2016
 */

#ifndef ACTIVEPIECE_H
#define ACTIVEPIECE_H
#include "ChessPiece.h"

struct ActivePiece
{
	ChessPiece *piece;
	int arrayLocation[2];
	char gameLocation[2];
};

#endif
