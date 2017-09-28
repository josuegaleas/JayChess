/*
 * Author: Josue Galeas
 * Last Edit: September 19, 2017
 */

#ifndef BOARD_H
#define BOARD_H

#include "Piece.hpp"
#include <unordered_map>

class Board
{
	private:
		Piece *board;
		void setupPieces(int);
		std::unordered_map<char, int> m;

	public:
		Board();
		~Board() {delete[] board;};
		Piece *getPiece(int, int) const;
		Piece *getPiece(int *) const;
		void setupSymbolOf(Piece *);
		void drawBoard() const;
};

#endif
