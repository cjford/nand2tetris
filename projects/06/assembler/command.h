#define C_COMMAND "C_COMMAND"
#define A_COMMAND "A_COMMAND"
#define L_COMMAND "L_COMMAND"

struct command {
  char* type;
  long symbol;
  char* dest;
  char* comp;
  char* jmp;
};
