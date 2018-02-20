/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.19
 */

#ifndef BOARD_H
#define BOARD_H

#include "Piece.hpp"
#include "Move.hpp"
#include <map>

class Board
{
	private:
		// Board
		Piece **board = new Piece*[8];
		std::string symbols[12] = {"♙", "♘", "♗", "♖", "♕", "♔", "♟", "♞", "♝", "♜", "♛", "♚"};
		std::map<char, int> mapping;
		void setPieces(int);
		// Pawn
		bool pawnPromotion = false;
		bool enPassant = false;
		bool ifPawnHelper(Move *);
		// King
		int *whiteKing = new int[2] {7, 4};
		int *blackKing = new int[2] {0, 4};
		int *rook = new int[3] {-1, -1, -1};
		bool castling = false;
		bool ifCastling(int *, char);

	public:
		// Board
		Board();
		~Board();
		void setSymbol(Piece *);
		Piece *getPiece(int x, int y) const {return &board[x][y];};
		Piece *getPiece(int *) const;
		// Pawn
		void setPawnPromotion() {pawnPromotion = false;};
		void setEnPassant() {enPassant = false;};
		bool getPawnPromotion() const {return pawnPromotion;};
		bool getEnPassant() const {return enPassant;};
		bool ifPawn(Move *);
		// King
		void setKing(char, int *);
		void setRook() {rook[0] = rook[1] = rook[2] = -1;};
		void setCastling() {castling = false;};
		int *getKing(char) const;
		int *getRook() const {return rook;};
		bool getCastling() const {return castling;};
		bool ifKing(Move *);
};

#endif
