#include "chip8.h"
#include "display.h"
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  // declare struct and variables
  Chip8 *chip8;
  Display *display;
  const char *filename = argv[1];

  // init systems
  chip8_init(chip8);
  chip8_load_rom(chip8, filename);
  display_init(display);

  // main emulator loop
  while (1) {
  }

  return 0;
}
