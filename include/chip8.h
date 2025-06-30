#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct{
  u_int8_t screen_width;
  u_int8_t screen_height;

  uint8_t memory[4096]; // 4k memory
  uint8_t V[16];        // 16 registers: V0 - VF
  uint16_t I;           // index registers
  uint16_t pc;          // Program counter

  uint16_t stack[16];  // Stack (for function calls)
  uint8_t sp;          // stack pointer
  uint8_t delay_timer; // Delay timer
  uint8_t sound_timer; // Sound timer

  uint8_t keypad[16];     // 16-key input
  uint8_t video[64 * 32];// monochrome display (1 byte per pixel)

  uint16_t opcode; // currently executing instruction

  bool draw_flag;
} Chip8;

void chip8_init(Chip8 * chip8);
void chip8_load_rom(Chip8 * chip8, const char * filename);
void chip8_emulate_cycles(Chip8 * chip8);

#endif //! CHIP8_H
