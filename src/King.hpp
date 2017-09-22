/*
 * Author: Josue Galeas
 * Last Edit: September 22, 2017
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
		int *white;
		int *black;
		bool ifCastling(int *, char, Board *);

	public:
		King();
		~King();
		void setCastling() {castling = false;};
		void setRook() {rook[0] = rook[1] = rook[2] = -1;};
		void setKing(char, int *);
		bool getCastling() const {return castling;};
		int *getRook() const {return rook;};
		int *getKing(char) const;
		bool ifKing(Move *, Board *);
};

#endif
