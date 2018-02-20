/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.20
 */

#ifndef VERIFICATION_H
#define VERIFICATION_H

#include "Board.hpp"

void updatePieces(Move *, Board *);
bool verifyCapture(Move *, Board *);
bool verifyMove(Move *, Board *);

#endif
