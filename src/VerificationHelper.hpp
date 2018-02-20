/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.20
 */

#ifndef VERIFICATIONHELPER_H
#define VERIFICATIONHELPER_H

#include "Board.hpp"

bool ifQueen(Move *, Board *);
bool ifBishop(Move *, Board *);
bool ifKnight(Move *, Board *);
bool ifRook(Move *, Board *);

#endif
