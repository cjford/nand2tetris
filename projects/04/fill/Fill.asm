// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

(LOOP)
  @write_val
  M=0

  // If no key is pressed, jump straight to WRITE_SCREEN with write_val as 0 (white)
  @KBD
  D=M
  @WRITE_SCREEN
  D;JEQ

  // If key is down, set write_val to -1 (black) before moving on to WRITE_SCREEN
  @write_val
  M=-1
  @WRITE_SCREEN
  0;JMP

// Reset write_pos to beginning of screen bitmap
(WRITE_SCREEN)
  @SCREEN
  D=A
  @write_pos
  M=D

// Loop through screen bitmap and set every register to current write_val
(WRITE_LOOP)
  @write_val
  D=M

  @write_pos
  A=M
  M=D

  // Once write_pos reaches the keyboard memory address (i.e. KBD - write_pos = 0),
  // we have written the entire screen. Jump back to main LOOP instead of WRITE_LOOP
  @write_pos
  M=M+1
  D=M
  @KBD
  D=A-D

  @LOOP
  D;JEQ

  @WRITE_LOOP
  0;JMP
