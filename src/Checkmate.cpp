/*
 * Author: Josue Galeas
 * Last Edit: September 26, 2017
 */

#include "Checkmate.hpp"
#include "Checking.hpp"
#include "Verification.hpp"
#include <cassert>
#include <vector>

struct Vectors
{
	std::vector<int *> enemies;
	std::vector<int *> allies;
	std::vector<int *> spots;
};

void addPos(std::vector<int *> *v, int *p)
{
	assert(v);
	assert(p);

	int *pos = new int[2];
	pos[0] = p[0];
	pos[1] = p[1];
	v->push_back(pos);
}

void deleteVectors(Vectors *v)
{
	while (!v->enemies.empty())
	{
		delete[] v->enemies.at(v->enemies.size() - 1);
		delete[] v->allies.at(v->allies.size() - 1);
		v->enemies.pop_back();
		v->allies.pop_back();
	}

	while (!v->spots.empty())
	{
		delete[] v->spots.at(v->spots.size() - 1);
		v->spots.pop_back();
	}
}

bool captureEnemy(Vectors *v, int *k, char p, Board *b)
{
	bool capture = false, escape = false;
	int ally[2], size = (int)v->enemies.size();
	char c = p == 'W' ? 'B':'W';

	for (int i = 0; i < size; i++)
	{
		capture |= inDangerEnemy(v->enemies.at(i), c, b, ally);
		addPos(&v->allies, ally);
	}

	if (capture)
	{
		for (int i = 0; i < size; i++)
		{
			if (v->allies.at(i)[0] != -1)
			{
				Piece backup;
				Piece *E = b->getPiece(v->enemies.at(i));
				Piece *P = b->getPiece(v->allies.at(i));
				backup.setPiece(E);
				E->setPiece(P);
				P->setPiece('E', 'E', false, "");

				escape |= inDanger(k, p, b);
				P->setPiece(E);
				E->setPiece(&backup);
			}
		}

		// FIXME: Still a bit iffy on the logic here.
		capture = !escape;
	}

	return capture;
}

bool inCheckmate(King *k, char p, Board *b)
{
	int temp[2], enemy[2];
	int *king = k->getKing(p);
	bool output = inDangerEnemy(king, p, b, enemy);
	if (!output)
		return false;

	Vectors v;
	addPos(&v.enemies, enemy);

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
			addPos(&v.spots, temp);

			if (verifyMove(&m, b))
			{
				Piece backup;
				Piece *K = b->getPiece(king);
				Piece *T = b->getPiece(temp);
				backup.setPiece(T);
				T->setPiece(K);
				K->setPiece('E', 'E', false, "");

				output &= inDangerEnemy(temp, p, b, enemy);
				addPos(&v.enemies, enemy);
				K->setPiece(T);
				T->setPiece(&backup);
			}
		}
	}

	bool capture;
	if (output)
		capture = captureEnemy(&v, king, p, b);
	if (capture)
		output = false;
	printf("Safe escape: %s\n", capture ? "true":"false");

	// FIXME: Might still prematurely end the game!
	deleteVectors(&v);
	return output;
}
