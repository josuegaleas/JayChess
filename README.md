# JayChess
Chess from scratch, using JNI and TensorFlow.

![Alpha](./images/alpha.png?raw=true)

## Features
- C++ back-end, using the TensorFlow C++ API
- Java front-end, using the Java Native Interface

## Building
To build, use `make all` from the main directory. However, the paths for the JNI headers are hard-coded with Java 10 and macOS in mind, and might not work on a different machine. There is also variations in how the JNI library is compiled based on the OS, and the makefile is building for macOS. Built with clang++ following the C++11 standard, and with Java 10.

## TODO
- [ ] Improve support for pawn promotion (currently only promotes to Queen)
- [ ] Improve checkmate code (might still prematurely end the game)
- [ ] Clean up AN code, possibly merge into the updatePieces function
- [ ] Add support for en passant
- [ ] Implement self-learning AI
- [ ] Implement more features on the GUI (such as saving games and a timer)
- [ ] Add support for PGN format
- [ ] Update algebraic notation to differentiate between pieces when necessary

## Programming References
- [Essential JNI](http://www.prenhall.com/ptrbooks/ptr_0139470298.html)
- [JNI Specification (Java 10)](https://docs.oracle.com/javase/10/docs/specs/jni/index.html)
- [Core Java APIs and the Java Runtime on OS X](https://developer.apple.com/library/archive/documentation/Java/Conceptual/Java14Development/05-CoreJavaAPIs/CoreJavaAPIs.html)
- [TensorFlow C++ API](https://www.tensorflow.org/api_guides/cc/guide)

## Chess References
- [FIDE Laws of Chess](https://www.fide.com/FIDE/handbook/LawsOfChess.pdf)
- [Chess Wiki Article](https://en.wikipedia.org/wiki/Chess)
- [Algebraic Notation Wiki Article](https://en.wikipedia.org/wiki/Algebraic_notation_(chess))
