/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.20
 */

#ifndef DANGER_H
#define DANGER_H

#include "Board.hpp"
#include <vector>
#include <tuple>

bool inDanger(int *, char, Board *);
bool inDangerEnemy(int *, char, Board *, std::vector<std::tuple<int, int>> &);

#endif
