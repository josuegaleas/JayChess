/*
 * Author: Josue Galeas
 * Last Edit: September 7, 2017
 */

#ifndef KING_H
#define KING_H

#include "Move.hpp"
#include "Board.hpp"

bool ifKing(Move *, Board *);

class King
{
	private:
		bool castling;
		int rookPos[3];
		bool ifCastling(int *, char, char, Board *);
	public:
		bool ifKing(Move *, Board *);
		void setCastling() {castling = false;};
		bool getCastling() {return castling;};
		int *getRookPos() {return rookPos;};
};

#endif
