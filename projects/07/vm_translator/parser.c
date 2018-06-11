#include "parser.h"

int set_curr_cmd(FILE *input_file, vm_command *curr_cmd, char *cmd_buffer) {
  clear_cmd(curr_cmd);
  memset(cmd_buffer, 0, strlen(cmd_buffer));

  if (fgets(cmd_buffer, 100, input_file)) {
    strip_comments(cmd_buffer);
    strip_whitespace(cmd_buffer);
    set_cmd_fields(curr_cmd, cmd_buffer);

    return 1;
  }
  return 0;
}

void clear_cmd(vm_command *curr_cmd) {
  curr_cmd -> cmd = NULL;
  curr_cmd -> arg1 = NULL;
  curr_cmd -> arg2 = NULL;
}

void strip_comments(char *cmd_buffer) {
  for(int i = 0; i < strlen(cmd_buffer); i++) {
    if (start_comment(&cmd_buffer[i])) {
      *(cmd_buffer+(sizeof(char)*i)) = '\0';
    }
  }
};

void strip_whitespace(char *cmd_buffer) {
  int start = 0;
  int end = strlen(cmd_buffer) - 1;
  while (isspace((unsigned char) cmd_buffer[start])) {
    start++;
  }

  while ((end >= start) && (isspace((unsigned char) cmd_buffer[end]))) {
    end--;
  }

  int i;
  for (i = start; i <= end; i++) {
    cmd_buffer[i - start] = cmd_buffer[i];
  }

  cmd_buffer[i - start] = '\0';
}

int is_blank(char *cmd_buffer) {
  for (int i = 0; i < strlen(cmd_buffer); i++) {
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

void set_cmd_fields(vm_command *curr_cmd, char *cmd_buffer) {
  if(strcmp(cmd_buffer, "") == 0) {
    return;
  } else {
    char* curr_token;
    char* tokens[3];

    tokens[0] = strtok(cmd_buffer, " ");

    for(int i = 1; (curr_token = strtok(NULL, " ")); i++) {
      tokens[i] = curr_token;
    }

    curr_cmd -> cmd = tokens[0];

    if ((strcmp(tokens[0], "push") == 0) || (strcmp(tokens[0], "pop") == 0)) {
      curr_cmd -> arg1 = tokens[1];
      curr_cmd -> arg2 = tokens[2];
    } else {
      curr_cmd -> arg1 = tokens[0];
      curr_cmd -> arg2 = tokens[1];
    }

    curr_cmd -> index++;
  }
}
