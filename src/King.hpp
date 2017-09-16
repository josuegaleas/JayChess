/*
 * Author: Josue Galeas
 * Last Edit: September 16, 2017
 */

#ifndef KING_H
#define KING_H

#include "Move.hpp"
#include "Board.hpp"

class King
{
	private:
		bool castling;
		int *rook;
		bool ifCastling(int *, char, Board *);

	public:
		King() {castling = false; rook = new int[3];};
		~King() {delete[] rook;};
		void setCastling() {castling = false;};
		void setRook() {rook[0] = rook[1] = rook[2] = -1;};
		bool getCastling() const {return castling;};
		int *getRook() const {return rook;};
		bool ifKing(Move *, Board *);
};

#endif
