#ifndef CODES_H
#define CODES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"

char *dest(char *dest_string);
char *comp(char *comp_string);
char *jmp(char *jmp_string);
void cmd_to_binary(Command *curr_cmd, char *output);
void *decimal_to_binary(long decimal_num, char *output);

#endif
