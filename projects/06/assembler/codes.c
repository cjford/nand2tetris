#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *dest(char *dest_string) {
  if (dest_string == NULL)             { return "000"; }
  if (strcmp(dest_string, "M") == 0)   { return "001"; }
  if (strcmp(dest_string, "D") == 0)   { return "010"; }
  if (strcmp(dest_string, "MD") == 0)  { return "011"; }
  if (strcmp(dest_string, "A") == 0)   { return "100"; }
  if (strcmp(dest_string, "AM") == 0)  { return "101"; }
  if (strcmp(dest_string, "AD") == 0)  { return "110"; }
  if (strcmp(dest_string, "AMD") == 0) { return "111"; }
}

char *comp(char *comp_string) {
  if (strcmp(comp_string, "0") == 0)   { return "0101010"; }
  if (strcmp(comp_string, "1") == 0)   { return "0111111"; }
  if (strcmp(comp_string, "-1") == 0)  { return "0111010"; }
  if (strcmp(comp_string, "D") == 0)   { return "0001100"; }
  if (strcmp(comp_string, "A") == 0)   { return "0110000"; }
  if (strcmp(comp_string, "!D") == 0)  { return "0001101"; }
  if (strcmp(comp_string, "!A") == 0)  { return "0110001"; }
  if (strcmp(comp_string, "-D") == 0)  { return "0001111"; }
  if (strcmp(comp_string, "-A") == 0)  { return "0110011"; }
  if (strcmp(comp_string, "D+1") == 0) { return "0011111"; }
  if (strcmp(comp_string, "A+1") == 0) { return "0110111"; }
  if (strcmp(comp_string, "D-1") == 0) { return "0001110"; }
  if (strcmp(comp_string, "A-1") == 0) { return "0110010"; }
  if (strcmp(comp_string, "D+A") == 0) { return "0000010"; }
  if (strcmp(comp_string, "D-A") == 0) { return "0010011"; }
  if (strcmp(comp_string, "A-D") == 0) { return "0000111"; }
  if (strcmp(comp_string, "D&A") == 0) { return "0000000"; }
  if (strcmp(comp_string, "D|A") == 0) { return "0010101"; }

  if (strcmp(comp_string, "M") == 0)   { return "1110000"; }
  if (strcmp(comp_string, "!M") == 0)  { return "1110001"; }
  if (strcmp(comp_string, "-M") == 0)  { return "1110011"; }
  if (strcmp(comp_string, "M+1") == 0) { return "1110111"; }
  if (strcmp(comp_string, "M-1") == 0) { return "1110010"; }
  if (strcmp(comp_string, "D+M") == 0) { return "1000010"; }
  if (strcmp(comp_string, "D-M") == 0) { return "1010011"; }
  if (strcmp(comp_string, "M-D") == 0) { return "1000111"; }
  if (strcmp(comp_string, "D&M") == 0) { return "1000000"; }
  if (strcmp(comp_string, "D|M") == 0) { return "1010101"; }
}

char *jmp(char *jmp_string) {
  if (jmp_string == NULL)             { return "000"; }
  if (strcmp(jmp_string, "JGT") == 0) { return "001"; }
  if (strcmp(jmp_string, "JEQ") == 0) { return "010"; }
  if (strcmp(jmp_string, "JGE") == 0) { return "011"; }
  if (strcmp(jmp_string, "JLT") == 0) { return "100"; }
  if (strcmp(jmp_string, "JNE") == 0) { return "101"; }
  if (strcmp(jmp_string, "JLE") == 0) { return "110"; }
  if (strcmp(jmp_string, "JMP") == 0) { return "111"; }
}

void *reverse_string(char *str) {
  int i = 0;
  int j = strlen(str) - 1;
  for(i, j; i < (strlen(str) / 2); i++, j--) {
    char tmp = str[j];
    str[j] = str[i];
    str[i] = tmp;
  }
}

void *decimal_to_binary(long decimal_num, char *output) {
  char bit_buffer[1];
  while (decimal_num > 0) {
    int rem = decimal_num % 2;
    sprintf(bit_buffer, "%i", rem);
    strcat(output, bit_buffer);
    decimal_num = decimal_num / 2;
  }

  reverse_string(output);
}
