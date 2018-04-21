#ifndef VM_COMMAND_H
#define VM_COMMAND_H

#define C_ADD "add"
#define C_PUSH "push"
#define C_POP "pop"
#define C_SUB "sub"
#define C_NEG "neg"
#define C_EQ "eq"
#define C_GT "gt"
#define C_LT "lt"
#define C_AND "and"
#define C_OR "or"
#define C_NOT "not"

typedef struct vm_command {
  char* cmd;
  char* arg1;
  char* arg2;
} vm_command;

#endif
