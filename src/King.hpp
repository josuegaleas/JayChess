/*
 * Author: Josue Galeas
 * Last Edit: September 29, 2017
 */

#ifndef KING_H
#define KING_H

#include "Move.hpp"
#include "Board.hpp"

class King
{
	private:
		int *white;
		int *black;
		bool castling;
		int *rook;
		bool ifCastling(int *, char, Board *);

	public:
		King();
		~King();
		void setKing(char, int *);
		void setCastling() {castling = false;};
		void setRook() {rook[0] = rook[1] = rook[2] = -1;};
		int *getKing(char) const;
		bool getCastling() const {return castling;};
		int *getRook() const {return rook;};
		bool ifKing(Move *, Board *);
};

#endif
