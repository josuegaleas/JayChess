BIN = ./bin/
SRC = ./src/

CC = g++-6
CFLAGS = -g -Wall
VG = valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes

JC = javac
JH = javah -jni
J = java

JAVA_HOME = /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home
JNICFLAGS = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin
JNILFLAGS = -dynamiclib

all: clean
	$(JC) -cp $(BIN) -d $(BIN) $(SRC)*.java


# $(CC) $(CFLAGS) $(BIN)Main.o $(BIN)Verification.o $(BIN)Game.o $(BIN)Board.o $(BIN)ChessPiece.o -o $(BIN)Chess.out

# Main.o: $(SRC)Main.cpp $(SRC)Game.h
# 	$(CC) $(CFLAGS) -c $(SRC)Main.cpp -o $(BIN)Main.o

# Verification.o: $(SRC)Verification.cpp $(SRC)Verification.h $(SRC)ActivePiece.h $(SRC)Board.h
# 	$(CC) $(CFLAGS) -c $(SRC)Verification.cpp -o $(BIN)Verification.o

# Game.o: $(SRC)Game.cpp $(SRC)Game.h $(SRC)ActivePiece.h $(SRC)Verification.h
# 	$(CC) $(CFLAGS) -c $(SRC)Game.cpp -o $(BIN)Game.o

Board.o: $(SRC)Board.cpp $(SRC)Board.h
	$(CC) $(CFLAGS) -c $(SRC)Board.cpp -o $(BIN)Board.o

Piece.o: $(SRC)Piece.cpp $(SRC)Piece.h
	$(CC) $(CFLAGS) -c $(SRC)Piece.cpp -o $(BIN)Piece.o

Testing.o: $(SRC)Testing.cpp
	$(CC) $(CFLAGS) -c $(SRC)Testing.cpp -o $(BIN)Testing.o

Test: clean Piece.o Board.o Testing.o
	$(CC) $(CFLAGS) $(BIN)Testing.o $(BIN)Board.o $(BIN)Piece.o -o $(BIN)JNIChess

JNItest:
	$(JC) -cp $(BIN) -d $(BIN) $(SRC)X.java
	$(JH) $(BIN)X -d $(SRC)
	$(CC) $(CFLAGS) $(JNICFLAGS) -c $(SRC)X.cpp -o $(BIN)X.o
	$(CC) $(CFLAGS) $(JNILFLAGS) -o $(LIB)libX.jnilib $(BIN)X.o
	$(J) -cp $(BIN):$(LIB) X

JNIheader:
	$(JC) -cp $(BIN) -d $(BIN) $(SRC)X.java
	$(JH) $(BIN)X -d $(SRC)

JNIcompile:
	$(CC) $(CFLAGS) $(JNICFLAGS) -c $(SRC)X.cpp -o $(BIN)X.o
	$(CC) $(CFLAGS) $(JNILFLAGS) -o $(LIB)libX.jnilib $(BIN)X.o
	$(J) -cp $(BIN):$(LIB) X

run:
	$(BIN)JNIChess

runVal:
	$(VG) $(BIN)JNIChess

runGUI:
	$(J) -cp $(BIN) GUI

clean:
	rm -rf $(BIN)*
