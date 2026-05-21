#ifndef CHIP8_H
#define CHIP8_H

#include "display.h"
#include "input.h"
#include "timer.h"

#include <bits/stdint-uintn.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t memory[4096];  // 4k memory: program starts at [0x200]
    uint8_t V[16];         // 16 registers: V0 - VF
    uint16_t index_reg;    // index registers
    uint16_t pc;           // Program counter
    uint16_t stack[16];   // Stack (for function calls)
    uint8_t sp;           // stack pointer
    uint16_t opcode;  // currently executing instruction
    bool vy_shift_quirk;
} Chip8;

void chip8_init(Chip8* chip8);
void chip8_load_rom(Chip8* chip8, const char* filename);
void chip8_emulate_cycles(Chip8* chip8, Display* display, Input* input, Timer* timer);

#endif  //! CHIP8_H
