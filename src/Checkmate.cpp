/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.25
 */

#include "Checkmate.hpp"
#include "Danger.hpp"
#include "Verification.hpp"
#include <cassert>

struct Vectors
{
	std::vector<std::tuple<int, int>> enemies;
	std::vector<std::tuple<int, int>> spots;
};

bool captureEnemy(Vectors &, int *, char, Board *);
bool blockEnemy(Vectors &, int *, char, Board *);

bool captureEnemy(Vectors &v, int *k, char col, Board *b)
{
	if (v.enemies.size() > 1)
		return false;

	int temp0[2], temp1, temp2;
	bool capture = false, cond = (col == 'W');
	char enemy = cond ? 'B':'W';

	std::tuple<int, int> temp3 = v.enemies.front();
	std::vector<std::tuple<int, int>> allies;
	Piece backup, *E, *P;

	temp0[0] = std::get<0>(temp3);
	temp0[1] = std::get<1>(temp3);
	capture = inDangerEnemy(temp0, enemy, b, allies);

	if (capture)
	{
		for (auto i = allies.begin(); i < allies.end(); i++)
		{
			temp1 = std::get<0>(*i);
			temp2 = std::get<1>(*i);

			E = b->getPiece(temp0);
			P = b->getPiece(temp1, temp2);

			if (P->getType() == 'K')
				printf("ERROR: The ally is a King.\n");

			backup.setPiece(E);
			E->setPiece(P);
			P->setPiece('E', 'E', false);

			capture &= inDanger(k, col, b);
			P->setPiece(E);
			E->setPiece(&backup);
			if (!capture)
				return true;
		}
	}

	return false;
}

bool blockEnemy(Vectors &v, int *k, char col, Board *b)
{
	if (v.spots.empty())
		return false;

	int temp0[2], temp1, temp2;
	bool block = false;

	std::vector<std::tuple<int, int>> allies;
	Piece backup, *E, *P;

	for (auto i = v.spots.begin(); i < v.spots.end(); i++)
	{
		temp0[0] = std::get<0>(*i);
		temp0[1] = std::get<1>(*i);
		block = inDangerEnemy(temp0, col, b, allies);

		if (block)
		{
			for (auto j = allies.begin(); j < allies.end(); j++)
			{
				temp1 = std::get<0>(*j);
				temp2 = std::get<1>(*j);

				E = b->getPiece(temp0);
				P = b->getPiece(temp1, temp2);

				if (P->getType() == 'K')
					printf("ERROR: The ally is a King.\n");

				backup.setPiece(E);
				E->setPiece(P);
				P->setPiece('E', 'E', false);

				block &= inDanger(k, col, b);
				P->setPiece(E);
				E->setPiece(&backup);
				if (!block)
					return true;
			}
		}
	}

	return false;
}

bool inCheckmate(char col, Board *b)
{
	assert(b);

	Vectors v;
	int *king = b->getKing(col);
	bool output = inDangerEnemy(king, col, b, v.enemies);

	if (!output)
		return false;

	Piece backup, *kingPiece, *tempPiece;
	int temp0, temp1, temp2[2];

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

			kingPiece = b->getPiece(king);
			tempPiece = b->getPiece(temp0, temp1);
			backup.setPiece(tempPiece);
			tempPiece->setPiece(kingPiece);
			kingPiece->setPiece('E', 'E', false);

			output &= inDanger(temp2, col, b);
			kingPiece->setPiece(tempPiece);
			tempPiece->setPiece(&backup);
			if (!output)
				return false;
		}
	}

	output &= !captureEnemy(v, king, col, b);
	output &= !blockEnemy(v, king, col, b);

	// FIXME: Might still prematurely end the game!
	return output;
}
