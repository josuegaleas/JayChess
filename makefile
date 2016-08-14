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

Chess: Main.o Board.o ChessPiece.o
	$(CC) $(FLAGS) $(BIN)Main.o $(BIN)Board.o $(BIN)ChessPiece.o -o $(BIN)Chess.out

Main.o: $(SRC)Main.cpp $(SRC)Board.h
	$(CC) $(FLAGS) -c $(SRC)Main.cpp -o $(BIN)Main.o

Board.o: $(SRC)Board.cpp $(SRC)Board.h $(SRC)ChessPiece.h
	$(CC) $(FLAGS) -c $(SRC)Board.cpp -o $(BIN)Board.o

ChessPiece.o: $(SRC)ChessPiece.cpp $(SRC)ChessPiece.h
	$(CC) $(FLAGS) -c $(SRC)ChessPiece.cpp -o $(BIN)ChessPiece.o
