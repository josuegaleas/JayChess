# Variables
BIN = bin/
SRC = src/

C = clang
CFLAGS = -std=c++11 -O0 -g -Weverything -Wno-c++98-compat
A = ar
AFLAGS = -rc

JC = javac
JH = javah
J = java

JAVA_HOME = /Library/Java/JavaVirtualMachines/jdk1.8.0_121.jdk/Contents/Home
JNICFLAGS = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin

# Convenience Targets
all: clean CPP JAVA JNI

clean:
	rm -rf $(BIN)*

run:
	$(J) -cp $(BIN) -Djava.library.path=$(BIN) JayChess

# Compilation Rules
$(BIN)%.o: $(SRC)%.cpp
	$(C) $(CFLAGS) -c $< -o $@

$(BIN)libObjects.a: $(BIN)Piece.o $(BIN)Move.o $(BIN)Board.o $(BIN)King.o $(BIN)Pawn.o
	$(A) $(AFLAGS) $@ $^

$(BIN)libMovement.a: $(BIN)VerificationHelper.o $(BIN)Verification.o $(BIN)Danger.o $(BIN)Checkmate.o $(BIN)AN.o
	$(A) $(AFLAGS) $@ $^

CPP: $(BIN)libObjects.a $(BIN)libMovement.a

JAVA:
	$(JC) -cp $(BIN) -d $(BIN) $(SRC)*.java

JNI:
	$(JH) -cp $(BIN) -d $(SRC) Board
	$(C) $(CFLAGS) $(JNICFLAGS) -c $(SRC)BoardJNI.cpp -o $(BIN)BoardJNI.o
	$(C) $(CFLAGS) -dynamiclib -o $(BIN)libBoardJNI.jnilib $(BIN)BoardJNI.o -L. $(BIN)libObjects.a $(BIN)libMovement.a
# $(CXX) $(CXXFLAGS) -dynamiclib -o $(BIN)libBoardJNI.jnilib $(BIN)BoardJNI.o -L. $(BIN)libObjects.a $(BIN)libMovement.a
