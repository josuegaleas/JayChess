/*
 * Author: Josue Galeas
 * Last Edit: August 23rd, 2016
 */

#ifndef VERIFICATION_H
#define VERIFICATION_H
#include "ActivePiece.hpp"
#include "Board.hpp"

bool ifKing(ActivePiece *, ActivePiece *);
bool ifQueen(ActivePiece *, ActivePiece *, Board *);
bool ifBishop(ActivePiece *, ActivePiece *, Board *);
bool ifKnight(ActivePiece *, ActivePiece *);
bool ifRook(ActivePiece *, ActivePiece *, Board *);
bool ifPawn(ActivePiece *, ActivePiece *);

#endif
