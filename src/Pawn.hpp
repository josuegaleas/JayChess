/*
 * Author: Josue Galeas
 * Last Edit: September 9, 2017
 */

#ifndef PAWN_H
#define PAWN_H

#include "Move.hpp"
#include "Board.hpp"

class Pawn
{
	private:
		bool promo;
		bool passant;
		bool ifPawnHelper(Move *, char, Board *);

	public:
		bool ifPawn(Move *, Board *);
		void setPromo() {promo = false;};
		void setPassant() {passant = false;};
		bool getPromo() const {return promo;};
		bool getPassant() const {return passant;};
};

#endif
