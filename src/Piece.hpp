/*
 * Author: Josue Galeas
 * Last Edit: August 28, 2017
 */

#ifndef PIECE_H
#define PIECE_H

#include <string>

class Piece
{
	private:
		char type;
		char color;
		bool moved;
		std::string symbol;

	public:
		Piece();
		void setType(char);
		void setColor(char);
		void setMoved();
		void setSymbol(std::string);
		void setPiece(char, char, std::string);
		void setPiece(Piece *);
		char getType() const {return type;}
		char getColor() const {return color;}
		bool getMoved() const {return moved;}
		std::string getSymbol() const {return symbol;}
};

#endif
