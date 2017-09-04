### Variables ###
BIN = bin/
SRC = src/

CXX = g++-7
CXXFLAGS = -g -Wall
ARFLAGS = -rv

JC = javac
JH = javah -jni
J = java

JAVA_HOME = /Library/Java/JavaVirtualMachines/jdk1.8.0_121.jdk/Contents/Home
JNICXXFLAGS = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin

### Convenience Targets ###
all: clean compileCPP compileJAVA JNI1 JNI2

clean:
	rm -rf $(BIN)*

run:
	$(BIN)BACKEND.out

runGUI:
	$(J) -cp $(BIN) -Djava.library.path=$(BIN) GUI

### Compilation Rules ###
$(BIN)%.o: $(SRC)%.cpp $(SRC)%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)libObjects.a: $(BIN)Piece.o $(BIN)Board.o $(BIN)Move.o
	ar $(ARFLAGS) $@ $^

$(BIN)Main.o: $(SRC)Main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

compileCPP: $(BIN)libObjects.a $(BIN)Main.o
	$(CXX) $(CXXFLAGS) $(BIN)Main.o -L. $(BIN)libObjects.a -o $(BIN)BACKEND.out

compileJAVA:
	$(JC) -cp $(BIN) -d $(BIN) $(SRC)*.java

JNI1:
	$(JH) -cp $(BIN) -d $(SRC) ChessPanel
	$(CXX) $(CXXFLAGS) $(JNICXXFLAGS) -c $(SRC)ChessPanel.cpp -o $(BIN)ChessPanel.o
	$(CXX) $(CXXFLAGS) -dynamiclib -o $(BIN)libChessPanel.jnilib $(BIN)ChessPanel.o

JNI2:
	$(JH) -cp $(BIN) -d $(SRC) ChessBoard
	$(CXX) $(CXXFLAGS) $(JNICXXFLAGS) -c $(SRC)ChessBoard.cpp -o $(BIN)ChessBoard.o
	$(CXX) $(CXXFLAGS) -dynamiclib -o $(BIN)libChessBoard.jnilib $(BIN)ChessBoard.o -L. $(BIN)libObjects.a
