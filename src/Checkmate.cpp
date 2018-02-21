/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.21
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

bool captureEnemy(Vectors &v, int *k, char p, Board *b)
{
	int temp[2];
	std::vector<std::tuple<int, int>> allies;
	bool capture = false, cond = p == 'W';
	char c = cond ? 'B':'W';

	for (auto i = v.enemies.begin(); i < v.enemies.end(); i++)
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

			if (inDanger(k, p, b))
				capture = false;
			P->setPiece(E);
			E->setPiece(&backup);
		}
		allies.clear();
	}

	return capture;
}

bool blockEnemy(Vectors &v, int *k, char p, Board *b)
{
	bool block = false;
	int ally[2], *temp;

	for (int i = 0; i < (int)v.spots.size(); i++)
	{
		temp = v.spots.at(i);
		block |= inDangerEnemy(temp, p, b, ally);

		if (ally[0] != -1)
		{
			Piece backup;
			Piece *E = b->getPiece(temp);
			Piece *P = b->getPiece(ally);
			backup.setPiece(E);
			E->setPiece(P);
			P->setPiece('E', 'E', false, "");

			if (inDanger(k, p, b))
				block = false;
			P->setPiece(E);
			E->setPiece(&backup);
		}
	}

	return block;
}

bool inCheckmate(char p, Board *b)
{
	assert(b);

	Vectors v;
	int temp1[2], temp2[2], *king = b->getKing(p);
	bool output = inDangerEnemy(king, p, b, v.initEnemies);

	if (!output)
		return false;

	std::vector<std::tuple<int, int>> enemy;
	Piece backup, *K, *T;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			temp1[0] = king[0] + i;
			temp1[1] = king[1] + j;

			if (temp1[0] < 0 || temp1[0] > 7)
				continue;
			if (temp1[1] < 0 || temp1[1] > 7)
				continue;

			if (b->getPiece(temp1)->getColor() == p)
				continue;

			Move m(king, temp1);
			v.spots.push_back(std::make_tuple(temp1[0], temp1[1]));

			// FIXME: Doesn't verifyMove already check if the new spot is not in danger?
			if (verifyMove(&m, b))
			{
				K = b->getPiece(king);
				T = b->getPiece(temp1);
				backup.setPiece(T);
				T->setPiece(K);
				K->setPiece('E', 'E', false, "");

				output &= inDangerEnemy(temp1, p, b, enemy);
				if (!output)
					return false;

				for (auto i = enemy.begin(); i < enemy.end(); i++)
				{
					temp2[0] = std::get<0>(*i);
					temp2[1] = std::get<1>(*i);
					v.addEnemies.push_back(std::make_tuple(temp2[0], temp2[1], temp1[0], temp1[1]));
				}

				K->setPiece(T);
				T->setPiece(&backup);
			}
		}
	}

	output &= !captureEnemy(v, king, p, b);
	output &= !blockEnemy(v, king, p, b);

	// FIXME: Might still prematurely end the game!
	return output;
}
