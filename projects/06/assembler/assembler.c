#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OUTPUT_EXTENSION ".hack"

char *get_output_filename(char* input_filename) {
  char *filename = malloc(sizeof(input_filename));
  strcpy(filename, input_filename);

  // Chop off everything after period
  char *extension_delim = strchr(filename, '.');
  *extension_delim = '\0';

  // Concat new extension
  strcat(filename, OUTPUT_EXTENSION);
  return filename;
}

int valid_args(int argc, char **argv) {
  printf("%ld", strlen(*argv));
  if (argc != 2) {
    printf("Requires single filename argument");
    return 0;
  }

  if (strcmp(strchr(argv[1], '.'), ".asm") != 0) {
    printf("Requires input file with .asm extension");
    return 0;
  }

  FILE* input_file = fopen(argv[1], "r");
  if (!input_file) {
    printf("Specified input file does not exist");
    return 0;
  }

  return 1;
}

int main(int argc, char **argv) {

  if (!(valid_args(argc, argv))) {
    return 1;
  }

  char *output_filename = get_output_filename(argv[1]);
  FILE *output_file = fopen(output_filename, "w");
  free(output_filename);
  // Parse and translate here, write to output_file
}
