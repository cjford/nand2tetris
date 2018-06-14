#include "code_writer.h"

void write_cmd(vm_command *command, FILE *output_file, char *static_prefix) {
  printf("=== write_cmd:\n");
  printf("cmd: %s \n", command -> cmd);
  printf("arg1: %s \n", command -> arg1);
  printf("arg2: %s \n", command -> arg2);
  printf("arg3: %s \n", command -> arg3);
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
    write_push(command, output_file, static_prefix);
  } else if (strcmp(command -> cmd, C_POP) == 0) {
    write_pop(command, output_file, static_prefix);
  } else if (strcmp(command -> cmd, C_LABEL) == 0) {
    write_label(command, output_file);
  } else if (strcmp(command -> cmd, C_GOTO) == 0) {
    write_goto(command, output_file);
  } else if (strcmp(command -> cmd, C_IF_GOTO) == 0) {
    write_if_goto(command, output_file);
  } else if (strcmp(command -> cmd, C_FUNCTION) == 0) {
    write_function(command, output_file);
  } else if (strcmp(command -> cmd, C_RETURN) == 0) {
    write_return(command, output_file);
  } else if (strcmp(command -> cmd, C_CALL) == 0) {
    write_call(command, output_file);
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

void write_push(vm_command *command, FILE *output_file, char *static_prefix) {
  if (strcmp(command -> arg1, "constant") == 0) {
    fprintf(output_file, "@%s\n", command -> arg2);
    fputs("D=A\n", output_file);
  } else {
    const char *segment_symbol = get_segment_symbol(command -> arg1, static_prefix);
    fprintf(output_file, "@%s\n", segment_symbol);

    if (is_indirect_address(command -> arg1)) {
      fputs("A=M\n", output_file);
    }

    write_offset_increment(command -> arg2, output_file);
    fputs("D=M\n", output_file);
  }

  fputs("@SP\n", output_file);
  fputs("A=M\n", output_file);
  fputs("M=D\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M+1\n", output_file);
}

void write_pop(vm_command *command, FILE *output_file, char *static_prefix) {
  const char *segment_symbol = get_segment_symbol(command -> arg1, static_prefix);
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("D=M\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M-1\n", output_file);

  fprintf(output_file, "@%s\n", segment_symbol);
  if (is_indirect_address(command -> arg1)) {
    fputs("A=M\n", output_file);
  }

  write_offset_increment(command -> arg2, output_file);
  fputs("M=D\n", output_file);
}

void write_label(vm_command *command, FILE *output_file) {
  fprintf(output_file, "(%s)\n", command -> arg2);
}

void write_goto(vm_command *command, FILE *output_file) {
  fprintf(output_file, "@%s\n", command -> arg2);
  fputs("0;JMP\n", output_file);
}

void write_if_goto(vm_command *command, FILE *output_file) {
  fputs("@SP\n", output_file);
  fputs("A=M-1\n", output_file);
  fputs("D=M\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M-1\n", output_file);
  fprintf(output_file, "@%s\n", command -> arg2);
  fputs("D;JNE\n", output_file);
}

void write_function(vm_command *command, FILE *output_file) {
  fprintf(output_file, "(%s)\n", command -> arg2);

  char *endptr = "";
  int local_count = strtol(command -> arg3, &endptr, 10);
  for (int i = 0; i < local_count; i++) {
    fputs("@SP\n", output_file);
    fputs("A=M\n", output_file);
    fputs("M=0\n", output_file);
    fputs("@SP\n", output_file);
    fputs("M=M+1\n", output_file);
  }
}

void write_return(vm_command *command, FILE *output_file) {
  fputs("@LCL\n", output_file);
  fputs("D=M\n", output_file);
  fputs("@R13\n", output_file);
  fputs("M=D\n", output_file);

  fputs("@LCL\n", output_file);
  fputs("A=M\n", output_file);
  write_offset_decrement("5", output_file);
  fputs("D=M\n", output_file);
  fputs("@R14\n", output_file);
  fputs("M=D\n", output_file);

  command -> arg1 = "argument";
  command -> arg2 = "0";
  write_pop(command, output_file, "");

  fputs("@ARG\n", output_file);
  fputs("D=M+1\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=D\n", output_file);

  fputs("@R13\n", output_file);
  fputs("A=M\n", output_file);
  write_offset_decrement("1", output_file);
  fputs("D=M\n", output_file);
  fputs("@THAT\n", output_file);
  fputs("M=D\n", output_file);

  fputs("@R13\n", output_file);
  fputs("A=M\n", output_file);
  write_offset_decrement("2", output_file);
  fputs("D=M\n", output_file);
  fputs("@THIS\n", output_file);
  fputs("M=D\n", output_file);

  fputs("@R13\n", output_file);
  fputs("A=M\n", output_file);
  write_offset_decrement("3", output_file);
  fputs("D=M\n", output_file);
  fputs("@ARG\n", output_file);
  fputs("M=D\n", output_file);

  fputs("@R13\n", output_file);
  fputs("A=M\n", output_file);
  write_offset_decrement("4", output_file);
  fputs("D=M\n", output_file);
  fputs("@LCL\n", output_file);
  fputs("M=D\n", output_file);

  fputs("@R14\n", output_file);
  fputs("A=M\n", output_file);
  fputs("0;JMP\n", output_file);
}

void write_call(vm_command *command, FILE *output_file) {
  fprintf(output_file, "@RETURN_%s_%i\n", command -> arg2, command -> index);
  fputs("D=A\n", output_file);
  fputs("@SP\n", output_file);
  fputs("A=M\n", output_file);
  fputs("M=D\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M+1\n", output_file);

  fputs("@LCL\n", output_file);
  fputs("D=M\n", output_file);
  fputs("@SP\n", output_file);
  fputs("A=M\n", output_file);
  fputs("M=D\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M+1\n", output_file);

  fputs("@ARG\n", output_file);
  fputs("D=M\n", output_file);
  fputs("@SP\n", output_file);
  fputs("A=M\n", output_file);
  fputs("M=D\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M+1\n", output_file);

  fputs("@THIS\n", output_file);
  fputs("D=M\n", output_file);
  fputs("@SP\n", output_file);
  fputs("A=M\n", output_file);
  fputs("M=D\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M+1\n", output_file);

  fputs("@THAT\n", output_file);
  fputs("D=M\n", output_file);
  fputs("@SP\n", output_file);
  fputs("A=M\n", output_file);
  fputs("M=D\n", output_file);
  fputs("@SP\n", output_file);
  fputs("M=M+1\n", output_file);

  fputs("@SP\n", output_file);
  fputs("A=M\n", output_file);
  write_offset_decrement(command -> arg3, output_file);
  write_offset_decrement("5", output_file);
  fputs("D=A\n", output_file);
  fputs("@ARG\n", output_file);
  fputs("M=D\n", output_file);

  fputs("@SP\n", output_file);
  fputs("D=M\n", output_file);
  fputs("@LCL\n", output_file);
  fputs("M=D\n", output_file);

  fprintf(output_file, "@%s\n", command -> arg2);
  fputs("0;JMP\n", output_file);
  fprintf(output_file, "(RETURN_%s_%i)\n", command -> arg2, command -> index);
}

const char *get_segment_symbol(char *segment_name, char *static_prefix) {
  if (strcmp(segment_name, "argument") == 0) { return "ARG"; }
  else if (strcmp(segment_name, "local") == 0) { return "LCL"; }
  else if ((strcmp(segment_name, "this") == 0) || strcmp(segment_name, "pointer") == 0) { return "THIS"; }
  else if (strcmp(segment_name, "temp") == 0) { return "R5"; }
  else if (strcmp(segment_name, "that") == 0) { return "THAT"; }
  else if (strcmp(segment_name, "static") == 0) { return static_prefix; }
  else {
    printf("Error: Invalid memory segment: %s\n", segment_name);
    exit(EXIT_FAILURE);
  }
}

void write_offset_increment(char *offset_string, FILE *output_file) {
  char *endptr = "";
  int offset = strtol(offset_string, &endptr, 10);
  for (int i = 0; i < offset; i++) {
    fputs("A=A+1\n", output_file);
  }
}

void write_offset_decrement(char *offset_string, FILE *output_file) {
  char *endptr = "";
  int offset = strtol(offset_string, &endptr, 10);
  for (int i = 0; i < offset; i++) {
    fputs("A=A-1\n", output_file);
  }
}

int is_indirect_address(char *segment_name) {
  return (
    strcmp(segment_name, "temp")    != 0 &&
    strcmp(segment_name, "pointer") != 0
  );
}
