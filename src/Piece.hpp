/*
 * Author: Josue Galeas
 * Last Edit: October 2, 2017
 */

#ifndef PIECE_H
#define PIECE_H

#include <string>

class Piece
{
	private:
		char type = 'E';
		char color = 'E';
		bool moved = false;
		std::string symbol = "";

	public:
		void setType(char t) {type = t;};
		void setColor(char c) {color = c;};
		void setSymbol(std::string s) {symbol = s;};
		void setMoved(bool m) {moved = m;};
		void setPiece(char, char, bool, std::string);
		void setPiece(Piece *);
		char getType() const {return type;}
		char getColor() const {return color;}
		bool getMoved() const {return moved;}
		std::string getSymbol() const {return symbol;}
};

#endif
