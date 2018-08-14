/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.14
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Piece.hpp"
#include "Move.hpp"

class Board
{
	private:
		Piece **board = new Piece*[8];
		void setColors(int);
		void setPawns(int);
		void setNonPawns(int);
		int *whiteKingPos = new int[2] {7, 4};
		int *blackKingPos = new int[2] {0, 4};
		int *rookPos = new int[2] {-1, -1};
		int *pawnPos = new int[2] {-1, -1};
		bool castling = false;
		bool checkmate = false;
		bool pawnPromotion = false;
		bool pawnMovedTwo = false;
		bool enPassant = false;
		bool ifCastling(int *, char);
		bool setPawnFlags();
		bool ifEnPassant(Move *, bool);
		bool ifPawnHelper(Move *);
		char padding[3];

	public:
		Board();
		~Board();
		Piece *getPiece(int x, int y) const {return &board[x][y];}
		Piece *getPiece(int *) const;
		void setKingPos(char, int *);
		void setRookPos() {rookPos[0] = rookPos[1] = -1;}
		void setPawnPos() {pawnPos[0] = pawnPos[1] = -1;}
		void setCastling() {castling = false;}
		void setCheckmate() {checkmate = true;}
		void setPawnPromotion() {pawnPromotion = false;}
		void setPawnMovedTwo() {pawnMovedTwo = false;}
		void setEnPassant() {enPassant = false;}
		int *getKingPos(char) const;
		int *getRookPos() const {return rookPos;}
		int *getPawnPos() const {return pawnPos;}
		bool getCastling() const {return castling;}
		bool getCheckmate() const {return checkmate;}
		bool getPawnPromotion() const {return pawnPromotion;}
		bool getPawnMovedTwo() const {return pawnMovedTwo;}
		bool getEnPassant() const {return enPassant;}
		bool ifKing(Move *);
		bool ifPawn(Move *);
};

#endif /* BOARD_HPP */
