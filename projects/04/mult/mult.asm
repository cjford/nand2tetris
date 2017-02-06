// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// Clear previous result
@R2
M=0

// Add the value of R1 to value of R2, and do it as many times as the value of R0
(LOOP)
  // Terminate when R0 reaches 0
  @R0
  D=M
  @END
  D;JEQ

  // Increase result value by value of R1
  @R1
  D=M
  @R2
  M=M+D

  // Decrement R0
  @R0
  M=M-1

  @LOOP
  0;JMP

(END)
  @END
  0;JMP
