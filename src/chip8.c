#include "chip8.h"
#include <bits/stdint-uintn.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void chip8_init(Chip8 * chip8) {
    chip8->pc = 0x200;
    chip8->I = 0;
    chip8->sp = 0;
    chip8->opcode = 0;
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
    chip8->draw_flag = false;

    memset(chip8->memory, 0, sizeof(chip8->memory));
    memset(chip8->V, 0, sizeof(chip8->V));
    memset(chip8->stack, 0, sizeof(chip8->stack));
    memset(chip8->keypad, 0, sizeof(chip8->keypad));
    memset(chip8->video, 0, sizeof(chip8->video));
}

void chip8_emulate_cycles(Chip8 * chip8) {
   
    chip8->opcode = chip8->memory[chip8->pc] << 8 | chip8->memory[chip8->pc + 1]; 
    chip8->pc += 2;
    int x = 0;
    int y = 0;

    uint8_t  N   = (chip8->opcode & 0x000F);
    uint8_t  NN  = (chip8->opcode & 0x00FF);
    uint16_t NNN = (chip8->opcode & 0x0FFF);
    uint8_t  X   = (chip8->opcode & 0x0F00) >> 8;
    uint8_t  Y   = (chip8->opcode & 0x00F0) >> 4; 

    switch (chip8->opcode & 0xF000) {
        case 0x0000:
            // 00E0: Clears the screen
            if (chip8->opcode == 0x00E0){
                memset(chip8->video, 0, sizeof(chip8->video));
                chip8->draw_flag = true;
            }
            // 00EE: Return from a subroutine.
            // Set the program counter to the address at the top of the stack
            else if (chip8->opcode == 0x00EE) {
               chip8->sp--;
               chip8->pc = chip8->stack[chip8->sp];
            }
            break;
        case 0x1000:
            // 1NNN: Jump to address NNN
            chip8->pc = NNN; 
            break;
        // case 0x2000:
        // case 0x3000:
        // case 0x4000:
        // case 0x5000:
        case 0x6000:
            // 6XNN: Set register X to NN
          chip8->V[X] = NN; 
            break;
        case 0x7000:
          chip8->V[X] += NN; 
            break;
        // case 0x8000:
        // case 0x9000:
        case 0xA000:
            // ANNN: Set the index register to the address NNN
            chip8->I = NNN; 
            break;
        // case 0xB000:
        // case 0xC000:
        case 0xD000:
            // DXYN: Draw a sprite at coordinate VX, VY using N bytes of sprite data
            // starting at the address stored in the index register if any set pixels
            // are unset set VF to 1. Otherwise, set VF to 0
            x = chip8->V[X];
            y = chip8->V[Y];
            chip8->V[0xF] = 0;
    
            for (int row = 0; row < N; row++) {
                int sprite = chip8->memory[chip8->I + row];
                for (int col = 0; col < 8; col++) {
                    //mask the pixel and get its values by shifting

                    //todo change pixel declaration to: int pixel = (sprite >> (7 - col)) & 1;
                    int pixel = (sprite & (0x80 >> col)) >> (7 - col);
                    if (pixel == 1) {
                        int x_cord = (x + col) % SCREEN_WIDTH;
                        int y_cord = (y + row) % SCREEN_HEIGHT;
                        // formula for 1D array : y * 64 + x
                        int index = (y_cord * SCREEN_WIDTH) + x_cord;

                        if (chip8->video[index] == 1) {
                            chip8->V[0xF] = 1;
                        }
                        chip8->video[index] ^= 1;
                    }
                }
            }
            chip8->draw_flag = true;
            break;
        // case 0xE000:
        case 0xF000:
        default:
            printf("error: unknown opcode 0x%04x\n", chip8->opcode & 0xF000);
            break;
    }
}

void chip8_load_rom(Chip8 * chip8, const char * filename) {
    FILE * rom = fopen(filename, "rb");
    if (rom == NULL) {
        printf("couldn't load rom\n");
    }

    // stores size of rom for checking
    fseek(rom, 0, SEEK_END);
    const long rom_size = ftell(rom);
    rewind(rom);

    fread(&chip8->memory[0x200], sizeof(uint8_t), rom_size, rom);
    if (sizeof(chip8->memory) < 4096) {
        if (rom_size > 4096 - 0x200) {
            printf("Error: Rom is to large for memory buffer\n");
        fclose(rom);
        return;
        }
    }
    fclose(rom);
    printf("rom loaded successfully...\n");
}

