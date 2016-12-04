BIN = ./bin/
SRC = ./src/

CC = g++-6
CFLAGS = -g -Wall
VG = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

JC = javac
JH = javah -jni
J = java

JAVA_HOME = /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home
JNICFLAGS = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin
JNILFLAGS = -dynamiclib

all: clean Main.o Verification.o Game.o Board.o ChessPiece.o
	$(CC) $(CFLAGS) $(BIN)Main.o $(BIN)Verification.o $(BIN)Game.o $(BIN)Board.o $(BIN)ChessPiece.o -o $(BIN)Chess.out
	$(JC) -cp $(BIN) -d $(BIN) $(SRC)*.java

Main.o: $(SRC)Main.cpp $(SRC)Game.h
	$(CC) $(CFLAGS) -c $(SRC)Main.cpp -o $(BIN)Main.o

Verification.o: $(SRC)Verification.cpp $(SRC)Verification.h $(SRC)ActivePiece.h $(SRC)Board.h
	$(CC) $(CFLAGS) -c $(SRC)Verification.cpp -o $(BIN)Verification.o

Game.o: $(SRC)Game.cpp $(SRC)Game.h $(SRC)ActivePiece.h $(SRC)Verification.h
	$(CC) $(CFLAGS) -c $(SRC)Game.cpp -o $(BIN)Game.o

Board.o: $(SRC)Board.cpp $(SRC)Board.h $(SRC)ActivePiece.h $(SRC)ChessPiece.h
	$(CC) $(CFLAGS) -c $(SRC)Board.cpp -o $(BIN)Board.o

ChessPiece.o: $(SRC)ChessPiece.cpp $(SRC)ChessPiece.h
	$(CC) $(CFLAGS) -c $(SRC)ChessPiece.cpp -o $(BIN)ChessPiece.o

JNItest:
	$(JC) -cp $(BIN) -d $(BIN) $(SRC)X.java
	$(JH) X -d $(SRC)
	$(CC) $(CFLAGS) $(JNICFLAGS) -c $(SRC)X.cpp -o $(BIN)X.o
	$(CC) $(CFLAGS) $(JNILFLAGS) -o $(LIB)libX.jnilib $(BIN)X.o
	$(J) -cp $(BIN):$(LIB) X

run:
	$(BIN)Chess.out

runVal:
	$(VG) $(BIN)Chess.out

runGUI:
	$(J) -cp $(BIN) GUI

clean:
	rm -rf $(BIN)*
