### Variables ###
BIN = bin/
SRC = src/

CXX = g++-7
CXXFLAGS = -g -Wall

JC = javac
JH = javah -jni
J = java

JAVA_HOME = /Library/Java/JavaVirtualMachines/jdk1.8.0_121.jdk/Contents/Home
JNICXXFLAGS = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin
JNILFLAGS = -dynamiclib

### Convenience Targets ###
all: clean ChessCPP ChessJAVA

clean:
	rm -rf $(BIN)*

run:
	$(BIN)ChessCPP

runGUI:
	$(J) -cp $(BIN) GUI

### Compilation Rules ###
$(BIN)Piece.o: $(SRC)Piece.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)Move.o: $(SRC)Move.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)Board.o: $(SRC)Board.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)King.o: $(SRC)King.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)Pawn.o: $(SRC)Pawn.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)Others.o: $(SRC)Others.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)Verification.o: $(SRC)Verification.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)Testing.o: $(SRC)Testing.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)libMain.a: $(BIN)Piece.o $(BIN)Move.o $(BIN)Board.o $(BIN)Testing.o
	ar rc $@ $^
	ranlib $@

$(BIN)libMovement.a: $(BIN)King.o $(BIN)Pawn.o $(BIN)Others.o $(BIN)Verification.o
	ar rc $@ $^
	ranlib $@

ChessCPP: $(BIN)libMain.a $(BIN)libMovement.a
	$(CXX) $(CXXFLAGS) -L. $^ -o $(BIN)$@

ChessJAVA:
	$(JC) -cp $(BIN) -d $(BIN) $(SRC)*.java

# JNItest:
# 	$(JC) -cp $(BIN) -d $(BIN) $(SRC)X.java
# 	$(JH) $(BIN)X -d $(SRC)
# 	$(CXX) $(CXXFLAGS) $(JNICXXFLAGS) -c $(SRC)X.cpp -o $(BIN)X.o
# 	$(CXX) $(CXXFLAGS) $(JNILFLAGS) -o $(LIB)libX.jnilib $(BIN)X.o
# 	$(J) -cp $(BIN):$(LIB) X

# JNIheader:
# 	$(JC) -cp $(BIN) -d $(BIN) $(SRC)X.java
# 	$(JH) $(BIN)X -d $(SRC)

# JNIcompile:
# 	$(CXX) $(CXXFLAGS) $(JNICXXFLAGS) -c $(SRC)X.cpp -o $(BIN)X.o
# 	$(CXX) $(CXXFLAGS) $(JNILFLAGS) -o $(LIB)libX.jnilib $(BIN)X.o
# 	$(J) -cp $(BIN):$(LIB) X
