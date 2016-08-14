/*
 * Author: Josue Galeas
 * Last Edit: August 13th, 2016
 */

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

class ChessPiece
{
	private:
		char pieceType;

	public:
		ChessPiece();
		void setType(char);
		char getType() const
		{
			return pieceType;
		}
};

#endif
