/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.20
 */

#ifndef VERIFICATION_HPP
#define VERIFICATION_HPP

#include "Board.hpp"

void updatePieces(Move *, Board *);
bool verifyCapture(Move *, Board *);
bool verifyMove(Move *, Board *);

#endif /* VERIFICATION_HPP */
