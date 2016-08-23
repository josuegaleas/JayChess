/*
 * Author: Josue Galeas
 * Last Edit: August 23rd, 2016
 */

#ifndef VERIFICATION_H
#define VERIFICATION_H
#include "ActivePiece.h"
#include "Board.h"

bool ifKing(ActivePiece *, ActivePiece *);
bool ifQueen(ActivePiece *, ActivePiece *);
bool ifBishop(ActivePiece *, ActivePiece *, Board *);
bool ifKnight(ActivePiece *, ActivePiece *);
bool ifRook(ActivePiece *, ActivePiece *);
bool ifPawn(ActivePiece *, ActivePiece *);

#endif
