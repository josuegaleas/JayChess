### Variables ###
BIN = bin/
SRC = src/

CXX = g++-7
CXXFLAGS = -g -Wall -Wextra -Wpedantic
A = ar
ARFLAGS = -rc

JC = javac
JH = javah -jni
J = java

JAVA_HOME = /Library/Java/JavaVirtualMachines/jdk1.8.0_121.jdk/Contents/Home
JNICXXFLAGS = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin

### Convenience Targets ###
all: clean CPP JAVA JNI

clean:
	rm -rf $(BIN)*

run:
	$(J) -cp $(BIN) -Djava.library.path=$(BIN) GUI

### Compilation Rules ###
$(BIN)%.o: $(SRC)%.cpp $(SRC)%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)King.o: $(SRC)King.cpp $(SRC)Board.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)Pawn.o: $(SRC)Pawn.cpp $(SRC)Board.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)libObjects.a: $(BIN)Piece.o $(BIN)Move.o $(BIN)Board.o $(BIN)King.o $(BIN)Pawn.o
	$(A) $(ARFLAGS) $@ $^

$(BIN)libMovement.a: $(BIN)VerificationHelper.o $(BIN)Verification.o $(BIN)Danger.o $(BIN)Checkmate.o $(BIN)AN.o
	$(A) $(ARFLAGS) $@ $^

CPP: $(BIN)libObjects.a $(BIN)libMovement.a

JAVA:
	$(JC) -cp $(BIN) -d $(BIN) $(SRC)*.java

JNI:
	$(JH) -cp $(BIN) -d $(SRC) Board
	$(CXX) $(CXXFLAGS) $(JNICXXFLAGS) -c $(SRC)BoardJNI.cpp -o $(BIN)BoardJNI.o
	$(CXX) $(CXXFLAGS) -dynamiclib -o $(BIN)libBoardJNI.jnilib $(BIN)BoardJNI.o -L. $(BIN)libObjects.a $(BIN)libMovement.a
