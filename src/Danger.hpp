/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.20
 */

#ifndef DANGER_HPP
#define DANGER_HPP

#include "Board.hpp"
#include <vector>

bool inDanger(int *, char, Board *);
bool inDangerEnemy(int *, char, Board *, std::vector<std::tuple<int, int>> &);

#endif /* DANGER_HPP */
