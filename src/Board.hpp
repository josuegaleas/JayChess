/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.02
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Piece.hpp"
#include "Move.hpp"

class Board
{
	private:
		// Board
		Piece **board = new Piece*[8];
		void setColors(int);
		void setPawns(int);
		void setNonPawns(int);
		// King
		int *whiteKingPos = new int[2] {7, 4};
		int *blackKingPos = new int[2] {0, 4};
		int *rookPos = new int[2] {-1, -1};
		bool castling = false;
		bool ifCastling(int *, char);
		// Pawn
		bool pawnPromotion = false;
		bool enPassant = false;
		bool ifPawnHelper(Move *);
		char padding[5];

	public:
		// Board
		Board();
		~Board();
		Piece *getPiece(int x, int y) const {return &board[x][y];}
		Piece *getPiece(int *) const;
		// King
		void setKing(char, int *);
		void setRook() {rookPos[0] = rookPos[1] = -1;}
		void setCastling() {castling = false;}
		int *getKing(char) const;
		int *getRook() const {return rookPos;}
		bool getCastling() const {return castling;}
		bool ifKing(Move *);
		// Pawn
		void setPawnPromotion() {pawnPromotion = false;}
		void setEnPassant() {enPassant = false;}
		bool getPawnPromotion() const {return pawnPromotion;}
		bool getEnPassant() const {return enPassant;}
		bool ifPawn(Move *);
};

#endif /* BOARD_HPP */
