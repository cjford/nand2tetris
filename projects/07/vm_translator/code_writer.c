#include "code_writer.h"

void write_cmd(vm_command *command, FILE *output_file) {
  printf("=== write_cmd:\n");
  printf("cmd: %s \n", command -> cmd);
  printf("arg1: %s \n", command -> arg1);
  printf("arg2: %s \n", command -> arg2);
  printf("index: %i \n", command -> index);

  if(strcmp(command -> cmd, C_ADD) == 0) {
    write_add(command, output_file);
  } else if (strcmp(command -> cmd, C_SUB) == 0) {
    write_sub(command, output_file);
  }  else if (strcmp(command -> cmd, C_NEG) == 0) {
    write_neg(command, output_file);
  }  else if (strcmp(command -> cmd, C_EQ) == 0) {
    write_eq(command, output_file);
  }  else if (strcmp(command -> cmd, C_GT) == 0) {
    write_gt(command, output_file);
  }  else if (strcmp(command -> cmd, C_LT) == 0) {
    write_lt(command, output_file);
  }  else if (strcmp(command -> cmd, C_AND) == 0) {
    write_and(command, output_file);
  }  else if (strcmp(command -> cmd, C_OR) == 0) {
    write_or(command, output_file);
  }  else if (strcmp(command -> cmd, C_NOT) == 0) {
    write_not(command, output_file);
  } else if (strcmp(command -> cmd, C_PUSH) == 0) {
    write_push(command, output_file);
  } else if (strcmp(command -> cmd, C_POP) == 0) {
    write_pop(command, output_file);
  } else {
    printf("ERROR: invalid command in VM input: %s\n", command -> cmd);
    exit(EXIT_FAILURE);
  }
}

void write_add(vm_command *command, FILE *output_file) {
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("D=M\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("M=D+M\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M-1\n", output_file);
}

void write_sub(vm_command *command, FILE *output_file) {
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("D=M\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("M=M-D\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M-1\n", output_file);
}

void write_neg(vm_command *command, FILE *output_file) {
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("D=M\n", output_file);
  fputs("M=-D\n", output_file);
}

void write_eq(vm_command *command, FILE *output_file) {
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);

  // Put top stack value in R13
  fputs("D=M\n", output_file);
  fputs("@R13\n", output_file);
  fputs("M=D\n", output_file);

  // Second stack value in D
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("D=M\n", output_file);

  // Difference in D
  fputs("@R13\n", output_file);
  fputs("D=M-D\n", output_file);

  fprintf(output_file, "@RETURN_EQ_%i\n", command -> index );
  fputs("D;JEQ\n", output_file);

  // Return 0 (false)
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("M=0\n", output_file);
  fprintf(output_file, "@DEC_SP_%i\n", command -> index );
  fputs("0;JMP\n", output_file);

  // Return -1 (true)
  fprintf(output_file, "(RETURN_EQ_%i)\n", command -> index );
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("M=-1\n", output_file);

  fprintf(output_file, "(DEC_SP_%i)\n", command -> index );
  fputs("@SP\n", output_file);
  fputs("M=M-1\n", output_file);
}

void write_gt(vm_command *command, FILE *output_file) {
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);

  fputs("D=M\n", output_file);
  fputs("@R13\n", output_file);
  fputs("M=D\n", output_file);

  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("D=M\n", output_file);

  fputs("@R13\n", output_file);
  fputs("D=D-M\n", output_file);

  fprintf(output_file, "@RETURN_GT_%i\n", command -> index );
  fputs("D;JGT\n", output_file);

  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("M=0\n", output_file);
  fprintf(output_file, "@DEC_SP_%i\n", command -> index );
  fputs("0;JMP\n", output_file);

  fprintf(output_file, "(RETURN_GT_%i)\n", command -> index );
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("M=-1\n", output_file);

  fprintf(output_file, "(DEC_SP_%i)\n", command -> index );
  fputs("@SP\n", output_file);
  fputs("M=M-1\n", output_file);
}

void write_lt(vm_command *command, FILE *output_file) {
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);

  fputs("D=M\n", output_file);
  fputs("@R13\n", output_file);
  fputs("M=D\n", output_file);

  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("D=M\n", output_file);

  fputs("@R13\n", output_file);
  fputs("D=D-M\n", output_file);

  fprintf(output_file, "@RETURN_LT_%i\n", command -> index );
  fputs("D;JLT\n", output_file);

  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("M=0\n", output_file);
  fprintf(output_file, "@DEC_SP_%i\n", command -> index );
  fputs("0;JMP\n", output_file);

  fprintf(output_file, "(RETURN_LT_%i)\n", command -> index );
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("M=-1\n", output_file);

  fprintf(output_file, "(DEC_SP_%i)\n", command -> index );
  fputs("@SP\n", output_file);
  fputs("M=M-1\n", output_file);
}

void write_and(vm_command *command, FILE *output_file) {
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("D=M\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("M=M&D\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M-1\n", output_file);
}

void write_or(vm_command *command, FILE *output_file) {
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("D=M\n", output_file);
  fputs("A=A-1\n", output_file);
  fputs("M=M|D\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M-1\n", output_file);
}

void write_not(vm_command *command, FILE *output_file) {
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("D=M\n", output_file);
  fputs("M=!D\n", output_file);
}

void write_push(vm_command *command, FILE *output_file) {
  if (strcmp(command -> arg1, "constant") == 0) {
    fprintf(output_file, "@%s\n", command -> arg2);
  } else {
    fprintf(output_file, "@%s\n", command -> arg1);
    fprintf(output_file, "A=A+%s\n", command -> arg2);
  }

  fputs("D=A\n", output_file);
  fputs("@SP\n", output_file);
  fputs("A=M\n", output_file);
  fputs("M=D\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M+1\n", output_file);
}

void write_pop(vm_command *command, FILE *output_file) {
  fputs("@SP\n", output_file);
  fputs("A=M\n", output_file);
  fputs("D=M\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M-1\n", output_file);
  fprintf(output_file, "@%s\n", command -> arg1);
  fprintf(output_file, "A=A+%s\n", command -> arg2);
  fputs("\n", output_file);
  fputs("M=D\n", output_file);
}