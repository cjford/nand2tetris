#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "command.h"

int set_curr_cmd(FILE *input_file, Command *curr_cmd, char *cmd_buffer);
int start_comment(char *cmd_buffer);
int is_blank(char *cmd_buffer);
void clear_cmd(Command *curr_cmd);
void strip_comments(char *cmd_buffer);
void strip_whitespace(char *cmd_buffer);
void set_cmd_fields(Command *curr_cmd, char *cmd_buffer);
void set_c_cmd_fields(Command *curr_cmd, char *cmd_buffer);
void set_a_cmd_fields(Command *curr_cmd, char *cmd_buffer);
void set_l_cmd_fields(Command *curr_cmd, char *cmd_buffer);

#endif
