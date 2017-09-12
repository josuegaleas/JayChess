/*
 * Author: Josue Galeas
 * Last Edit: September 12, 2017
 */

#ifndef KING_H
#define KING_H

#include "Move.hpp"
#include "Board.hpp"

class King
{
	private:
		bool castling;
		int *rookPos;
		bool ifCastling(int *, char, Board *);

	public:
		King() {castling = false; rookPos = new int[3];};
		~King() {delete[] rookPos;};
		bool ifKing(Move *, Board *);
		void setCastling() {castling = false;};
		bool getCastling() const {return castling;};
		int *getRookPos() const {return rookPos;};
};

#endif
