#include "chip8.h"
#include <stdint.h>
#include <stdio.h>
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
  FILE *rom;
  rom = fopen(filename, "rb");
  if (rom == NULL) {
    printf("couldnt load rom\n");
  }
  fread(chip8->memory, sizeof(uint8_t), 4096, rom);
  if (sizeof(chip8->memory) < 4096) {
    if (ferror(rom)) {
      printf("Error loading rom\n");
    }
    if (feof(rom)) {
      printf("Error: reached end of file\n");
    }
  }
  printf("rom loaded succesfully...\n");
}
