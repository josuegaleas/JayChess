/*
 * Author: Josue Galeas
 * Last Edit: September 26, 2017
 */

#include "Checkmate.hpp"
#include "Checking.hpp"
#include "Verification.hpp"
#include <cassert>
#include <vector>
#include <algorithm>

struct Vectors
{
	std::vector<int *> enemies;
	std::vector<int *> spots;
};

void addPos(std::vector<int *> &v, int *p)
{
	assert(p);

	int *pos = new int[2];
	std::copy(p, p + 2, pos);
	v.push_back(pos);
}

void deleteVectors(Vectors &v)
{
	while (!v.enemies.empty())
	{
		delete[] v.enemies.at(v.enemies.size() - 1);
		v.enemies.pop_back();
	}

	while (!v.spots.empty())
	{
		delete[] v.spots.at(v.spots.size() - 1);
		v.spots.pop_back();
	}
}

bool captureEnemy(Vectors &v, int *k, char p, Board *b)
{
	bool capture = false;
	int ally[2], *temp;
	char c = p == 'W' ? 'B':'W';

	for (int i = 0; i < (int)v.enemies.size(); i++)
	{
		temp = v.enemies.at(i);
		capture |= inDangerEnemy(temp, c, b, ally);

		if (ally[0] != -1)
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

bool inCheckmate(char p, Game *g)
{
	assert(g);

	Board *b = &g->board;
	int temp[2], enemy[2];
	int *king = g->king.getKing(p);
	bool output = inDangerEnemy(king, p, b, enemy);

	if (!output)
		return false;

	Vectors v;
	addPos(v.enemies, enemy);

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			temp[0] = king[0] + i;
			temp[1] = king[1] + j;

			if (temp[0] < 0 || temp[0] > 7)
				continue;
			if (temp[1] < 0 || temp[1] > 7)
				continue;

			if (b->getPiece(temp)->getColor() == p)
				continue;

			Move m(king, temp);
			addPos(v.spots, temp);

			if (verifyMove(&m, b))
			{
				Piece backup;
				Piece *K = b->getPiece(king);
				Piece *T = b->getPiece(temp);
				backup.setPiece(T);
				T->setPiece(K);
				K->setPiece('E', 'E', false, "");

				output &= inDangerEnemy(temp, p, b, enemy);
				addPos(v.enemies, enemy);
				K->setPiece(T);
				T->setPiece(&backup);
			}
		}
	}

	output &= !captureEnemy(v, king, p, b);
	output &= !blockEnemy(v, king, p, b);

	// FIXME: Might still prematurely end the game!
	deleteVectors(v);
	return output;
}
