#ifndef CODE_WRITER_H
#define CODE_WRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm_command.h"

void write_cmd(vm_command *command, FILE *output_file);
void write_add(vm_command *command, FILE *output_file);
void write_sub(vm_command *command, FILE *output_file);
void write_neg(vm_command *command, FILE *output_file);
void write_eq(vm_command *command, FILE *output_file);
void write_gt(vm_command *command, FILE *output_file);
void write_lt(vm_command *command, FILE *output_file);
void write_and(vm_command *command, FILE *output_file);
void write_or(vm_command *command, FILE *output_file);
void write_not(vm_command *command, FILE *output_file);
void write_push(vm_command *command, FILE *output_file);
void write_pop(vm_command *command, FILE *output_file);

#endif