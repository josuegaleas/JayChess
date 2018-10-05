# JayChess
Chess from scratch, using JNI and TensorFlow.

![Example](https://raw.githubusercontent.com/josuegaleas/jay-images/master/chess.png)

## Features
- C++ back-end, using the TensorFlow C++ API
- Java front-end, using the Java Native Interface

## Building
To build, use `make all` from the main directory. The paths for the JNI headers are hard-coded with Java 11 and macOS in mind, and **might not work** on your machine without editing `JAVA_HOME` and `JNICFLAGS` in the makefile. There are also variations in how the JNI library is compiled based on the OS, and the makefile is building for macOS in mind. Refer to the `JNI` rule in the makefile and adjust the rule to your OS.

Built with clang++ following the C++11 standard, and with Java 11. After building, use `make run` to start the program.

## TODO
- [ ] Improve support for pawn promotion (currently only promotes to a queen)
- [x] Add support for en passant
- [ ] Look for edge cases involving en passant
- [ ] Look for edge cases in the checkmate verification code
- [ ] Implement AI using TensorFlow
- [ ] Implement more features on the GUI (such as saving games and a timer)
- [ ] Add support for the PGN format
- [ ] Update algebraic notation code to differentiate between pieces when necessary

## Programming References
- [Essential JNI](http://www.prenhall.com/ptrbooks/ptr_0139470298.html)
- [JNI Specification (Java 11)](https://docs.oracle.com/en/java/javase/11/docs/specs/jni/index.html)
- [Core Java APIs and the Java Runtime on OS X](https://developer.apple.com/library/archive/documentation/Java/Conceptual/Java14Development/05-CoreJavaAPIs/CoreJavaAPIs.html)
- [TensorFlow C++ API](https://www.tensorflow.org/api_guides/cc/guide)
- [Deep Learning for Chess](https://erikbern.com/2014/11/29/deep-learning-for-chess.html)

## Chess References
- [FIDE Laws of Chess](https://www.fide.com/FIDE/handbook/LawsOfChess.pdf)
- [Chess Wiki Article](https://en.wikipedia.org/wiki/Chess)
- [Algebraic Notation Wiki Article](https://en.wikipedia.org/wiki/Algebraic_notation_(chess))
- [Portable Game Notation Wiki Article](https://en.wikipedia.org/wiki/Portable_Game_Notation)
