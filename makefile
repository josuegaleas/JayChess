### Variables ###
BIN = bin/
LIB = lib/
SRC = src/
RM = rm -rf

CXX = g++-6
CXXFLAGS = -g -Wall
VGFLAGS = -v --leak-check=full --show-leak-kinds=all --track-origins=yes

JC = javac
JH = javah -jni
J = java

JAVA_HOME = /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home
JNICXXFLAGS = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin
JNILFLAGS = -dynamiclib

### Convenience Targets ###
all: clean ChessCPP ChessJAVA

clean:
	$(RM) $(BIN)*

run:
	$(BIN)ChessCPP

runVal:
	valgrind $(VGFLAGS) $(BIN)ChessCPP

runGUI:
	$(J) -cp $(BIN) GUI

### Compilation Rules ###
$(BIN)Piece.o: $(SRC)Piece.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)Move.o: $(SRC)Move.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)Board.o: $(SRC)Board.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)Testing.o: $(SRC)Testing.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

ChessCPP: $(BIN)Piece.o $(BIN)Move.o $(BIN)Board.o $(BIN)Testing.o
	$(CXX) $(CXXFLAGS) $^ -o $(BIN)$@

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
