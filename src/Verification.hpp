/*
 * Author: Josue Galeas
 * Last Edit: September 7, 2017
 */

#ifndef VERIFICATION_H
#define VERIFICATION_H

#include "Move.hpp"
#include "Board.hpp"

void updatePieces(Move *, Board *);
bool verifyCapture(Move *, Board *);
bool verifyMove(Move *, Board*);

#endif
