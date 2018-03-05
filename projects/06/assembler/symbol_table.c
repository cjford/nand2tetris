#include "symbol_table.h"


SymbolEntry *st_initialize() {
  SymbolEntry *st_head = (SymbolEntry *) malloc(sizeof(SymbolEntry));

  // Predefined Symbols
  char *s = "SP";
  st_add_entry(st_head, s, 0);
  s = "LCL";
  st_add_entry(st_head, s, 1);
  s = "ARG";
  st_add_entry(st_head, s, 2);
  s = "THIS";
  st_add_entry(st_head, s, 3);
  s = "THAT";
  st_add_entry(st_head, s, 4);
  s = "R0";
  st_add_entry(st_head, s, 0);
  s = "R1";
  st_add_entry(st_head, s, 1);
  s = "R2";
  st_add_entry(st_head, s, 2);
  s = "R3";
  st_add_entry(st_head, s, 3);
  s = "R4";
  st_add_entry(st_head, s, 4);
  s = "R5";
  st_add_entry(st_head, s, 5);
  s = "R6";
  st_add_entry(st_head, s, 6);
  s = "R7";
  st_add_entry(st_head, s, 7);
  s = "R8";
  st_add_entry(st_head, s, 8);
  s = "R9";
  st_add_entry(st_head, s, 9);
  s = "R10";
  st_add_entry(st_head, s, 10);
  s = "R11";
  st_add_entry(st_head, s, 11);
  s = "R12";
  st_add_entry(st_head, s, 12);
  s = "R13";
  st_add_entry(st_head, s, 13);
  s = "R14";
  st_add_entry(st_head, s, 14);
  s = "R15";
  st_add_entry(st_head, s, 15);
  s = "SCREEN";
  st_add_entry(st_head, s, 16384);
  s = "KBD";
  st_add_entry(st_head, s, 24576);

  return st_head;
}

void st_add_entry(SymbolEntry *st_head, char *symbol, int address) {
  SymbolEntry * new_entry = (SymbolEntry *) malloc(sizeof(SymbolEntry));
  strcpy(new_entry->symbol, symbol);
  new_entry->address = address;
  new_entry->next = NULL;

  SymbolEntry * tail = st_head;
  while(tail->next != NULL) {
    tail = tail->next;
  }

  tail->next = new_entry;
}

void st_translate_cmd(SymbolEntry *st_head, Command *curr_cmd) {
  if (strcmp(curr_cmd -> type, A_COMMAND) != 0) { return; }

  long address = st_symbol_to_address(st_head, curr_cmd -> symbol);
  if (address == -1) {
    st_add_entry(st_head, curr_cmd->symbol, st_next_open_address(st_head));
  }

  curr_cmd -> address = address;
}

void st_print(SymbolEntry *st_head) {
  printf("SYMBOL TABLE ====\n");
  SymbolEntry * current = st_head;
  printf("Symbol: %s\n", current->symbol);
  printf("Address: %i\n\n", current->address);
  while(current->next != NULL) {
    current = current->next;
    printf("Symbol: %s\n", current->symbol);
    printf("Address: %i\n\n", current->address);
  }
  printf("======\n");
}

int st_next_open_address(SymbolEntry *st_head) {
  int max = 15;
  SymbolEntry * tail = st_head;

  while(tail->next != NULL) {
    tail = tail->next;
    if(tail->address >= max) {
      max = tail->address;
    }
  }

  return max + 1;
}

long st_symbol_to_address(SymbolEntry *st_head, char * symbol) {
  SymbolEntry * tail = st_head;
  while(tail != NULL) {
    if(strcmp(tail->symbol, symbol) == 0) {
      return tail->address;
    }

    tail = tail->next;
  }

  return -1;
}
