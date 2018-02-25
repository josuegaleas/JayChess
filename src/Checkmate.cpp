/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.23
 */

#include "Checkmate.hpp"
#include "Danger.hpp"
#include "Verification.hpp"
#include <cassert>

struct Vectors
{
	std::vector<std::tuple<int, int>> initEnemies;
	std::vector<std::tuple<int, int, int, int>> addEnemies;
	std::vector<std::tuple<int, int>> spots;
};

/*
bool captureEnemy(Vectors &v, int *k, char col, Board *b)
{
	int temp[2];
	std::vector<std::tuple<int, int>> allies;
	bool capture = false, cond = col == 'W';
	char c = cond ? 'B':'W';

	// TODO: If there is more than one initEnemy, why bother taking that
	// enemy out when the other initEnemy can take out the King?
	// So should it just skip to blocking?

	for (auto i = v.initEnemies.begin(); i < v.initEnemies.end(); i++)
	{
		// Look for allies that can take out enemy?
		temp[0] = std::get<0>(*i);
		temp[1] = std::get<1>(*i);
		capture |= inDangerEnemy(temp, c, b, allies);

		// Check if there is at least on ally?
		// If so, check if King is safe after kill
		if (!allies.empty())
		{
			Piece backup;
			Piece *E = b->getPiece(temp);
			Piece *P = b->getPiece(ally);
			backup.setPiece(E);
			E->setPiece(P);
			P->setPiece('E', 'E', false, "");

			if (inDanger(k, col, b))
				capture = false;
			P->setPiece(E);
			E->setPiece(&backup);
		}
		allies.clear();
	}

	return capture;
}
*/

/*
bool blockEnemy(Vectors &v, int *k, char col, Board *b)
{
	bool block = false;
	int ally[2], *temp;

	for (int i = 0; i < (int)v.spots.size(); i++)
	{
		temp = v.spots.at(i);
		block |= inDangerEnemy(temp, col, b, ally);

		if (ally[0] != -1)
		{
			Piece backup;
			Piece *E = b->getPiece(temp);
			Piece *P = b->getPiece(ally);
			backup.setPiece(E);
			E->setPiece(P);
			P->setPiece('E', 'E', false, "");

			if (inDanger(k, col, b))
				block = false;
			P->setPiece(E);
			E->setPiece(&backup);
		}
	}

	return block;
}
*/

bool inCheckmate(char col, Board *b)
{
	assert(b);

	Vectors v;
	int *king = b->getKing(col);
	bool output = inDangerEnemy(king, col, b, v.initEnemies);

	if (!output)
		return false;

	Piece backup, *K, *T;
	int temp0, temp1, temp2[2];
	std::tuple<int, int, int, int> temp3;
	std::vector<std::tuple<int, int>> enemy;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			temp0 = king[0] + i;
			temp1 = king[1] + j;

			if (temp0 < 0 || temp0 > 7)
				continue;
			if (temp1 < 0 || temp1 > 7)
				continue;

			if (b->getPiece(temp0, temp1)->getColor() == col)
				continue;

			temp2[0] = temp0;
			temp2[1] = temp1;
			v.spots.push_back(std::make_tuple(temp0, temp1));

			K = b->getPiece(king);
			T = b->getPiece(temp0, temp1);
			backup.setPiece(T);
			T->setPiece(K);
			K->setPiece('E', 'E', false, "");

			output &= inDangerEnemy(temp2, col, b, enemy);
			if (!output)
				return false;

			for (auto i = enemy.begin(); i < enemy.end(); i++)
			{
				temp2[0] = std::get<0>(*i);
				temp2[1] = std::get<1>(*i);
				temp3 = std::make_tuple(temp2[0], temp2[1], temp0, temp1);
				v.addEnemies.push_back(temp3);
			}

			K->setPiece(T);
			T->setPiece(&backup);
		}
	}

	/* output &= !captureEnemy(v, king, col, b); */
	/* output &= !blockEnemy(v, king, col, b); */

	// FIXME: Might still prematurely end the game!
	return output;
}
