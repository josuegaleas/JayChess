/*
 * Author: Josue Galeas
 * Last Edit: September 29, 2017
 */

#ifndef BOARD_H
#define BOARD_H

#include "Piece.hpp"
#include <array>
#include <unordered_map>

class Board
{
	private:
		Piece *board;
		std::array<std::string, 12> symbols;
		std::unordered_map<char, int> mapping;
		void setMapping();
		void setPieces(int);

	public:
		Board();
		~Board() {delete[] board;};
		void setSymbol(Piece *);
		Piece *getPiece(int, int) const;
		Piece *getPiece(int *) const;
};

#endif
