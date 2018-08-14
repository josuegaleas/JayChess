/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.14
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
/* void printVectors(Vectors &, Board *); */

bool captureEnemy(Vectors &v, int *king, char col, Board *b)
{
	// If there is more than one enemy, there is no escape, return false.
	if (v.enemies.size() > 1)
		return false;

	assert(king);
	assert(b);

	int temp0[2], temp1, temp2;
	bool capture = false;
	char enemyColor = flipColor(col);

	std::tuple<int, int> temp3 = v.enemies.front();
	std::vector<std::tuple<int, int>> allies;
	Piece backup, *enemyPiece, *allyPiece;

	// Get position of the enemy, see if its in danger and what allies can take it out.
	temp0[0] = std::get<0>(temp3);
	temp0[1] = std::get<1>(temp3);
	capture = inDangerEnemy(temp0, enemyColor, b, allies);

	if (capture)
	{
		for (auto i = allies.begin(); i < allies.end(); i++)
		{
			temp1 = std::get<0>(*i);
			temp2 = std::get<1>(*i);

			enemyPiece = b->getPiece(temp0);
			allyPiece = b->getPiece(temp1, temp2);

			// We can't move the king.
			if (allyPiece->getType() == 'K')
				continue;

			backup.setPiece(enemyPiece);
			enemyPiece->setPiece(allyPiece);
			allyPiece->setPiece('E', 'E', false);

			// After ally has captured the enemy, see if the king is now safe.
			capture &= inDanger(king, col, b);
			allyPiece->setPiece(enemyPiece);
			enemyPiece->setPiece(&backup);
			if (!capture)
			{
				/* printf("We can capture the enemy!\n"); */
				/* printf("Using %c%c at %d, %d.\n", allyPiece->getColor(), allyPiece->getType(), temp1, temp2); */
				return true;
			}
		}
	}

	/* printf("We can't capture the enemy...\n"); */
	return false;
}

bool blockEnemy(Vectors &v, int *king, char col, Board *b)
{
	// FIXME: Logic is a bit flawed, limited to only spots around the king.
	// Doesn't consider blocking the enemy's path from a different spot.

	// If there are no spots around the king, there is no escape, return false.
	if (v.spots.empty())
		return false;

	assert(king);
	assert(b);

	int temp0[2], temp1, temp2;
	bool block = false;
	char enemyColor = flipColor(col);

	std::vector<std::tuple<int, int>> allies;
	Piece backup, *enemyPiece, *allyPiece;

	for (auto i = v.spots.begin(); i < v.spots.end(); i++)
	{
		// Get position of the spot, see if its in danger and what allies can move there.
		temp0[0] = std::get<0>(*i);
		temp0[1] = std::get<1>(*i);
		block = inDangerEnemy(temp0, enemyColor, b, allies);

		if (block)
		{
			for (auto j = allies.begin(); j < allies.end(); j++)
			{
				temp1 = std::get<0>(*j);
				temp2 = std::get<1>(*j);

				enemyPiece = b->getPiece(temp0);
				allyPiece = b->getPiece(temp1, temp2);

				// We can't move the king.
				if (allyPiece->getType() == 'K')
					continue;

				backup.setPiece(enemyPiece);
				enemyPiece->setPiece(allyPiece);
				allyPiece->setPiece('E', 'E', false);

				// After ally has moved to the spot, see if the king is now safe.
				block &= inDanger(king, col, b);
				allyPiece->setPiece(enemyPiece);
				enemyPiece->setPiece(&backup);
				if (!block)
				{
					/* printf("We can block the enemy!\n"); */
					/* printf("Using %c%c at %d, %d.\n", allyPiece->getColor(), allyPiece->getType(), temp1, temp2); */
					return true;
				}
			}
		}
	}

	/* printf("We can't block the enemy...\n"); */
	return false;
}

/*
void printVectors(Vectors &v, Board *b)
{
	int temp[2];
	Piece *tempPiece;

	printf("Enemies:\n");

	for (auto i = v.enemies.begin(); i < v.enemies.end(); i++)
	{
		temp[0] = std::get<0>(*i);
		temp[1] = std::get<1>(*i);
		tempPiece = b->getPiece(temp);
		printf("%c%c at %d, %d\n", tempPiece->getColor(), tempPiece->getType(), temp[0], temp[1]);
	}

	printf("Spots:\n");

	for (auto i = v.spots.begin(); i < v.spots.end(); i++)
	{
		temp[0] = std::get<0>(*i);
		temp[1] = std::get<1>(*i);
		tempPiece = b->getPiece(temp);
		printf("%c%c at %d, %d\n", tempPiece->getColor(), tempPiece->getType(), temp[0], temp[1]);
	}
}
*/

bool inCheckmate(char col, Board *b)
{
	assert(b);

	Vectors vec;
	int *king = b->getKingPos(col);
	bool output = inDangerEnemy(king, col, b, vec.enemies);

	// If king is safe already, then just return false.
	if (!output)
		return false;

	Piece backup, *kingPiece, *tempPiece;
	int temp0, temp1, temp2[2];

	// Look for an empty spot, or an enemy piece to capture.
	// Check if that spot is safe, and if so return false.
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
			vec.spots.push_back(std::make_tuple(temp0, temp1));

			kingPiece = b->getPiece(king);
			tempPiece = b->getPiece(temp0, temp1);
			// We make a backup because it could be an enemy piece.
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

	// Suppose that the king can't escape the check,
	// then see if we can capture or block the enemy.
	// FIXME: Might still prematurely end the game!
	return !(captureEnemy(vec, king, col, b) || blockEnemy(vec, king, col, b));
}
