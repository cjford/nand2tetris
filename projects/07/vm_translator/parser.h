#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "vm_command.h"

int set_curr_cmd(FILE *input_file, vm_command *curr_cmd, char *cmd_buffer);
int start_comment(char *cmd_buffer);
int is_blank(char *cmd_buffer);
void strip_comments(char *cmd_buffer);
void strip_whitespace(char *cmd_buffer);
void clear_cmd(vm_command *curr_cmd);
void set_cmd_fields(vm_command *curr_cmd, char *cmd_buffer);

#endif
