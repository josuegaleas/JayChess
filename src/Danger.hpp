/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.04
 */

#ifndef DANGER_HPP
#define DANGER_HPP

#include "Board.hpp"
#include <vector>

char flipColor(char);
bool inDanger(int *, char, Board *);
bool inDangerEnemy(int *, char, Board *, std::vector<std::tuple<int, int>> &);

#endif /* DANGER_HPP */
