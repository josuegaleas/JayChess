/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.19
 */

#ifndef OTHERS_H
#define OTHERS_H

#include "Move.hpp"
#include "Board.hpp"

bool ifQueen(Move *, Board *);
bool ifBishop(Move *, Board *);
bool ifKnight(Move *, Board *);
bool ifRook(Move *, Board *);

#endif
