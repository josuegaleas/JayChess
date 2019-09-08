# Variables
BIN = bin/
SRC = src/

C = clang++
CFLAGS = -std=c++11 -g -Weverything -Wno-c++98-compat
A = ar
AFLAGS = -rc

JC = javac
J = java

JAVA_HOME = /Library/Java/JavaVirtualMachines/openjdk-12.0.2.jdk/Contents/Home
JNICFLAGS = -Wno-reserved-id-macro -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin

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

$(BIN)libMovement.a: $(BIN)VerificationHelper.o $(BIN)Verification.o $(BIN)Danger.o $(BIN)Checkmate.o $(BIN)JNIHelper.o
	$(A) $(AFLAGS) $@ $^

CPP: $(BIN)libObjects.a $(BIN)libMovement.a

JAVA:
	$(JC) -cp $(BIN) -d $(BIN) -h $(SRC) $(SRC)*.java

JNI:
	$(C) $(CFLAGS) $(JNICFLAGS) -c $(SRC)JNI.cpp -o $(BIN)JNI.o
	$(C) $(CFLAGS) -dynamiclib -o $(BIN)libJNI.jnilib $(BIN)JNI.o -L. $(BIN)libObjects.a $(BIN)libMovement.a
