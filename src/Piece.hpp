/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.02
 */

#ifndef PIECE_HPP
#define PIECE_HPP

class Piece
{
	private:
		char color = 'E';
		char type = 'E';
		bool moved = false;

	public:
		void setColor(char c) {color = c;}
		void setType(char t) {type = t;}
		void setMoved(bool m) {moved = m;}
		void setPiece(char, char, bool);
		void setPiece(Piece *);
		char getColor() const {return color;}
		char getType() const {return type;}
		bool getMoved() const {return moved;}
};

#endif /* PIECE_HPP */
