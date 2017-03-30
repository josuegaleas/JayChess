/*
 * Author: Josue Galeas
 * Last Edit: March 29, 2017
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
		char getType() const {return type;}
		char getColor() const {return color;}
		bool getMoved() const {return moved;}
		std::string getSymbol() const {return symbol;}
};

#endif
