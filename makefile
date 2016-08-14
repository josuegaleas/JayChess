BIN = ./bin/
SRC = ./src/

CC = g++
FLAGS = -Wall
RM = rm -rf

default: Chess

run:
	$(BIN)Chess.out

clean:
	$(RM) $(BIN)*

Chess: $(SRC)Main.cpp $(SRC)Board.h Board.o ChessPiece.o
	$(CC) $(FLAGS) $(SRC)Main.cpp $(BIN)Board.o $(BIN)ChessPiece.o -o $(BIN)Chess.out

Board.o: $(SRC)Board.cpp $(SRC)Board.h $(SRC)ChessPiece.h
	$(CC) $(FLAGS) -c $(SRC)Board.cpp -o $(BIN)Board.o

ChessPiece.o: $(SRC)ChessPiece.cpp $(SRC)ChessPiece.h
	$(CC) $(FLAGS) -c $(SRC)ChessPiece.cpp -o $(BIN)ChessPiece.o
