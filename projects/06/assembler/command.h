#ifndef COMMAND_H
#define COMMAND_H

#define C_COMMAND "C_COMMAND"
#define A_COMMAND "A_COMMAND"
#define L_COMMAND "L_COMMAND"

struct command {
  char* type;
  long address;
  char symbol[20];
  char* dest;
  char* comp;
  char* jmp;
};

#endif
