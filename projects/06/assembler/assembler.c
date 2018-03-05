#include "assembler.h"

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
  } else {
    fclose(input_file);
  }

  return 1;
}

int main(int argc, char **argv) {
  if (!(valid_args(argc, argv))) {
    return 1;
  } else {
    printf("Parsing file %s\n", argv[1]);
  }

  char *output_filename = get_output_filename(argv[1]);
  FILE *output_file = fopen(output_filename, "w");
  FILE *input_file = fopen(argv[1], "r");
  printf("Outputting to file %s\n", output_filename);
  free(output_filename);

  if (input_file == NULL || output_file == NULL) { exit(EXIT_FAILURE); }

  Command curr_cmd;
  char cmd_buffer[100];
  char instruction_buffer[15];

  int curr_address = 0;

  SymbolEntry *st_head = st_initialize();

  while (set_curr_cmd(input_file, &curr_cmd, cmd_buffer)) {
    if (!curr_cmd.type) { continue; }

    if (strcmp(curr_cmd.type, L_COMMAND) == 0) {

      if (st_head -> symbol == NULL) {
        strcpy(st_head -> symbol,  curr_cmd.symbol);
        st_head -> address = curr_address;
      } else {
        st_add_entry(st_head, curr_cmd.symbol, curr_address);
      }

    } else {
      curr_address++;
    }
  }

  rewind(input_file);

  while (set_curr_cmd(input_file, &curr_cmd, cmd_buffer)) {
    strcpy(instruction_buffer, "");
    if (curr_cmd.type && strcmp(curr_cmd.type, L_COMMAND) != 0) {
      st_translate_cmd(st_head, &curr_cmd);
      cmd_to_binary(&curr_cmd, instruction_buffer);
      fprintf(output_file, "%s\n", instruction_buffer);
    }
  }

  printf("Done\n");
  fclose(output_file);
  fclose(input_file);
}
