#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "command.h"

typedef struct SymbolEntry SymbolEntry;

typedef struct SymbolEntry {
  char symbol[100];
  int address;
  SymbolEntry *next;
} SymbolEntry;

SymbolEntry *st_initialize();
void st_add_entry(SymbolEntry *st_head, char *symbol, int address);
void st_translate_cmd(SymbolEntry *st_head, Command *curr_cmd);
void st_print(SymbolEntry *st_head);
int st_next_open_address(SymbolEntry *st_head);
long st_symbol_to_address(SymbolEntry * head, char * symbol);

#endif
