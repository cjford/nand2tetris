#ifndef CODES_H
#define CODES_H

char *dest(char *dest_string);
char *comp(char *comp_string);
char *jmp(char *jmp_string);
void cmd_to_binary(struct command *curr_cmd, char *output);
void *decimal_to_binary(long decimal_num, char *output);

#endif
