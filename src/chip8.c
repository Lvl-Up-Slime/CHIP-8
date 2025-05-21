#include "chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chip8_init(Chip8 *chip8) {
  chip8->pc = 0x200;
  chip8->I = 0;
  chip8->sp = 0;
  chip8->opcode = 0;

  memset(chip8->memory, 0, sizeof(chip8->memory));
  memset(chip8->V, 0, sizeof(chip8->V));
  memset(chip8->stack, 0, sizeof(chip8->stack));
  memset(chip8->keypad, 0, sizeof(chip8->keypad));
  memset(chip8->video, 0, sizeof(chip8->video));
}

void chip8_load_rom(Chip8 *chip8, const char *filename) {
  FILE *f = fopen(filename, "rb");
  if (!f) {
    printf("could not open ROM:%s", filename);
    exit(1);
  }

  fseek(f, 0, SEEK_END);
  size_t size = ftell(f);
  rewind(f);

  fread(&chip8->memory[0x200], size, 1, f);
  fclose(f);
}
