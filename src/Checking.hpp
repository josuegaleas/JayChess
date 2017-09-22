/*
 * Author: Josue Galeas
 * Last Edit: September 22, 2017
 */

#ifndef CHECKING_H
#define CHECKING_H

#include "Board.hpp"
#include "King.hpp"

bool inDanger(int *, char, Board *);
bool inCheckmate(King *, char, Board *);

#endif
