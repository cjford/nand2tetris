#include "vm_translator.h"

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

  char *filename = malloc(sizeof(argv[1]));
  strcpy(filename, argv[1]);

  char *extension_delim = strchr(filename, '.');
  *extension_delim = '\0';

  char static_prefix[sizeof(filename)];
  strcpy(static_prefix, filename);

  strcat(filename, OUTPUT_EXTENSION);
  char *output_filename =  filename;

  FILE *output_file = fopen(output_filename, "w");
  FILE *input_file = fopen(argv[1], "r");
  printf("Outputting to file %s\n", output_filename);
  free(output_filename);
  vm_command curr_cmd;

  char cmd_buffer[100];
  if (input_file == NULL || output_file == NULL) { exit(EXIT_FAILURE); }

  write_init(output_file);
  while (set_curr_cmd(input_file, &curr_cmd, cmd_buffer)) {
    if(curr_cmd.cmd != NULL && strcmp(curr_cmd.cmd, "") != 0) {
      write_cmd(&curr_cmd, output_file, static_prefix);
    }
  }
}
