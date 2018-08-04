/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.04
 */

#ifndef JNIHELPER_HPP
#define JNIHELPER_HPP

#include "Board.hpp"
#include <string>

void updatePieces(Move *, Board *);
std::string getAN(Move *, Board *);
void getANCheck(std::string &, Board *);

#endif /* JNIHELPER_HPP */
