/*
 * Author: Josue Galeas
 * Last Edit: August 13th, 2016
 */

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

class ChessPiece
{
	private:
		char type;
		char color;

	public:
		ChessPiece();
		void setType(char);
		void setColor(char);
		char getType() const
		{
			return type;
		}
		char getColor() const
		{
			return color;
		}
};

#endif
