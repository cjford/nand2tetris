#include "vm_translator.h"

void translate_file(FILE *input_file, FILE *output_file, char *static_prefix) {
  vm_command curr_cmd;
  curr_cmd.index = 0;
  char cmd_buffer[100];

  while (set_curr_cmd(input_file, &curr_cmd, cmd_buffer)) {
    if(curr_cmd.cmd != NULL && strcmp(curr_cmd.cmd, "") != 0) {
      write_cmd(&curr_cmd, output_file, static_prefix);
    }
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Requires single filename or directory argument\n");
    exit(EXIT_FAILURE);
  }

  char *filename = malloc(sizeof(argv[1]));
  strcpy(filename, argv[1]);

  char *extension_delim = strchr(filename, '.');
  if (extension_delim) { *extension_delim = '\0'; }

  strcat(filename, OUTPUT_EXTENSION);
  char *output_filename = filename;
  FILE *output_file = fopen(output_filename, "w");

  FILE *input_file;
  DIR *input_dir;
  if ((input_dir = opendir(argv[1])) != NULL) {
    write_init(output_file);

    struct dirent *dir_item;
    while ((dir_item = readdir(input_dir)) != NULL) {
      if (!strstr(dir_item -> d_name, INPUT_EXTENSION)) { continue; }

      char *dir_item_path = malloc(sizeof(argv[1]) + sizeof(dir_item -> d_name) + 1);
      strcpy(dir_item_path, argv[1]);
      strcat(dir_item_path, "/");
      strcat(dir_item_path, dir_item -> d_name);

      if ((input_file = fopen(dir_item_path, "r"))) {
        translate_file(input_file, output_file, dir_item -> d_name);
      }
    }
  } else if ((input_file = fopen(argv[1], "r")) != NULL) {
    write_init(output_file);
    translate_file(input_file, output_file, filename);
  } else {
    printf("Couldn't open specified file or directory\n");
    exit(EXIT_FAILURE);
  }

  printf("Output to file %s\n", output_filename);
}
