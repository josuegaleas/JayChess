BIN = ./bin/
SRC = ./src/

CC = g++
FLAGS = -Wall

all: Main.o Game.o Board.o ChessPiece.o
	$(CC) $(FLAGS) $(BIN)Main.o $(BIN)Game.o $(BIN)Board.o $(BIN)ChessPiece.o -o $(BIN)Chess.out

Main.o: $(SRC)Main.cpp $(SRC)Game.h
	$(CC) $(FLAGS) -c $(SRC)Main.cpp -o $(BIN)Main.o

Game.o: $(SRC)Game.cpp $(SRC)Game.h
	$(CC) $(FLAGS) -c $(SRC)Game.cpp -o $(BIN)Game.o

Board.o: $(SRC)Board.cpp $(SRC)Board.h
	$(CC) $(FLAGS) -c $(SRC)Board.cpp -o $(BIN)Board.o

ChessPiece.o: $(SRC)ChessPiece.cpp $(SRC)ChessPiece.h
	$(CC) $(FLAGS) -c $(SRC)ChessPiece.cpp -o $(BIN)ChessPiece.o

run:
	$(BIN)Chess.out

clean:
	rm -rf $(BIN)*
