/*
 * Author: Josue Galeas
 * Last Edit: September 12, 2017
 */

#ifndef VERIFICATION_H
#define VERIFICATION_H

#include "Move.hpp"
#include "Game.hpp"

void updatePieces(Move *, Game *);
bool verifyCapture(Move *, Game *);
bool verifyMove(Move *, Game *);
bool verifyMove(Move *, Board *);

#endif
