#ifndef CODE_WRITER_H
#define CODE_WRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm_command.h"

void write_cmd(vm_command *command, FILE *output_file, char *static_prefix);
void write_add(vm_command *command, FILE *output_file);
void write_sub(vm_command *command, FILE *output_file);
void write_neg(vm_command *command, FILE *output_file);
void write_eq(vm_command *command, FILE *output_file);
void write_gt(vm_command *command, FILE *output_file);
void write_lt(vm_command *command, FILE *output_file);
void write_and(vm_command *command, FILE *output_file);
void write_or(vm_command *command, FILE *output_file);
void write_not(vm_command *command, FILE *output_file);
void write_push(vm_command *command, FILE *output_file, char *static_prefix);
void write_pop(vm_command *command, FILE *output_file, char *static_prefix);
void write_label(vm_command *command, FILE *output_file);
void write_goto(vm_command *command, FILE *output_file);
void write_if_goto(vm_command *command, FILE *output_file);
void write_function(vm_command *command, FILE *output_file);
void write_return(vm_command *command, FILE *output_file);
void write_call(vm_command *command, FILE *output_file);
void write_init(FILE *output_file);
const char *get_segment_symbol(vm_command *command, char *static_prefix);
void write_offset_increment(vm_command *command, FILE *output_file);
void write_offset_decrement(char *offset_string, FILE *output_file);
int is_indirect_address(char *segment_name);

#endif
