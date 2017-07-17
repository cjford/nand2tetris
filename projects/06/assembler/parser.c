#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"

#define C_COMMAND "C_COMMAND"
#define A_COMMAND "A_COMMAND"
#define L_COMMAND "L_COMMAND"

int set_curr_cmd(FILE *input_file, struct command *curr_cmd, char *cmd_buffer) {
  clear_cmd(curr_cmd);
  if (fgets(cmd_buffer, 100, input_file)) {
    printf("===== cmd_buffer: %s", cmd_buffer);
    strip_comments(cmd_buffer);
    strip_whitespace(cmd_buffer);
    set_cmd_fields(curr_cmd, cmd_buffer);

    return 1;
  }
  return 0;
}

void clear_cmd(struct command *curr_cmd) {
  curr_cmd -> symbol = 0;
  curr_cmd -> type = NULL;
  curr_cmd -> dest = NULL;
  curr_cmd -> comp = NULL;
  curr_cmd -> jmp  = NULL;
}

void strip_comments(char *cmd_buffer) {
  int i = 0;
  for(i; i < strlen(cmd_buffer); i++) {
    if (start_comment(&cmd_buffer[i])) {
      *(cmd_buffer+(sizeof(char)*i)) = '\0';
    }
  }
};

void strip_whitespace(char *cmd_buffer) {
  int start = 0;
  int end = strlen(cmd_buffer) - 1;
  while(isspace((unsigned char) cmd_buffer[start])) {
    start++;
  }

  while((end >= start) && (isspace((unsigned char) cmd_buffer[end]))) {
    end--;
  }

  int i;
  for (i = start; i <= end; i++) {
    cmd_buffer[i - start] = cmd_buffer[i];
  }

  cmd_buffer[i - start] = '\0';
}

int is_blank(char *cmd_buffer) {
  int i = 0;
  for(i; i < strlen(cmd_buffer); i++) {
    if (!isspace((unsigned char) cmd_buffer[i])){
      return 0;
    }
  }

  return 1;
}

int start_comment(char *cmd_buffer) {
  if (strncmp(cmd_buffer, "//", 2) == 0) {
    return 1;
  } else {
    return 0;
  }
}

void set_cmd_fields(struct command *curr_cmd, char *cmd_buffer) {
  if (strchr(cmd_buffer, '@')) {
    curr_cmd -> type = A_COMMAND;
    set_a_cmd_fields(curr_cmd, cmd_buffer);
  } else if (strchr(cmd_buffer, '=') || strchr(cmd_buffer, ';')) {
    curr_cmd -> type = C_COMMAND;
    set_c_cmd_fields(curr_cmd, cmd_buffer);
  } else if (strchr(cmd_buffer, '(') && strchr(cmd_buffer, ')')) {
    curr_cmd -> type = L_COMMAND;
  }
}

void set_c_cmd_fields(struct command *curr_cmd, char *cmd_buffer) {
  char *dest_end = strchr(cmd_buffer, '=');
  if (dest_end) {
    *dest_end = '\0';
    curr_cmd -> dest = cmd_buffer;
    cmd_buffer = dest_end + sizeof(char);
  }

  char *comp_end = strchr(cmd_buffer, ';');
  if (comp_end) {
    *comp_end = '\0';
    curr_cmd -> comp = cmd_buffer;
    cmd_buffer = comp_end + sizeof(char);
    curr_cmd -> jmp = cmd_buffer;
  } else {
    curr_cmd -> comp = cmd_buffer;
  }
};

void set_a_cmd_fields(struct command *curr_cmd, char *cmd_buffer) {
  char **str_end;
  char *val = strchr(cmd_buffer, '@') + sizeof(char);
  long i = strtol(val, str_end, 10);
  curr_cmd -> symbol=i;
};

void set_l_cmd_fields(struct command *curr_cmd, char *cmd_buffer) {  };
