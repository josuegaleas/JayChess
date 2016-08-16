/*
 * Author: Josue Galeas
 * Last Edit: August 16th, 2016
 */

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

class ChessPiece
{
	private:
		char type;
		char color;
		char tile;

	public:
		ChessPiece();
		void setType(char);
		void setColor(char);
		void setTile(char);
		char getType() const
		{
			return type;
		}
		char getColor() const
		{
			return color;
		}
		char getTile() const
		{
			return tile;
		}
};

#endif
