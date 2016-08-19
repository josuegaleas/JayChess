/*
 * Author: Josue Galeas
 * Last Edit: August 19th, 2016
 */

#ifndef MOVINGPIECE_H
#define MOVINGPIECE_H
#include "ChessPiece.h"

struct MovingPiece
{
	ChessPiece *piece;
	int arrayLocation[2];
	char gameLocation[2];
};

#endif
