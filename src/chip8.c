#include "chip8.h"

#include <bits/stdint-intn.h>
#include <bits/stdint-uintn.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chip8_init(Chip8* chip8) {
    chip8->pc = 0x200;
    chip8->index_reg = 0;
    chip8->sp = 0;
    chip8->opcode = 0;
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
    chip8->vy_shift_quirk = 0;
    chip8->draw_flag = false;

    memset(chip8->memory, 0, sizeof(chip8->memory));
    memset(chip8->V, 0, sizeof(chip8->V));
    memset(chip8->stack, 0, sizeof(chip8->stack));
    memset(chip8->keypad, 0, sizeof(chip8->keypad));
    memset(chip8->video, 0, sizeof(chip8->video));
}

void chip8_emulate_cycles(Chip8* chip8) {
    chip8->opcode =
        chip8->memory[chip8->pc] << 8 | chip8->memory[chip8->pc + 1];
    chip8->pc += 2;

    int x = 0;
    int y = 0;

    uint8_t N = (chip8->opcode & 0x000F);
    uint8_t NN = (chip8->opcode & 0x00FF);
    uint16_t NNN = (chip8->opcode & 0x0FFF);
    uint8_t X = (chip8->opcode & 0x0F00) >> 8;
    uint8_t Y = (chip8->opcode & 0x00F0) >> 4;

    uint8_t key_pressed = 0;

    switch (chip8->opcode & 0xF000) {
        case 0x0000:
            // 00E0: Clears the screen
            if (chip8->opcode == 0x00E0) {
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
        case 0x2000:
            // 2NNN: Pushes program counter to the stack (subroutine NNN) that
            // will be popped by 00EE once subroutine returns from its process
            chip8->stack[chip8->sp] = chip8->pc;
            chip8->sp++;
            chip8->pc = NNN;
            break;
        case 0x3000:
            // 3XNN: If register X equals NN then skip next instruction
            if (chip8->V[X] == NN) {
                chip8->pc += 2;
            }
            break;
        case 0x4000:
            // 4XNN: If register X does not equals NN then skip next instruction
            if (chip8->V[X] != NN) {
                chip8->pc += 2;
            }
            break;
        case 0x5000:
            // 5XY0: If register X and Y are equals then skip next instruction
            if (chip8->V[X] == chip8->V[Y]) {
                chip8->pc += 2;
            }
            break;
        case 0x6000:
            // 6XNN: Set register X to NN
            chip8->V[X] = NN;
            break;
        case 0x7000:
            chip8->V[X] += NN;
            break;
        case 0x8000:
            // 8XY0 - 8XY7 and 8XYE runs arithmetic instruction
            switch (N) {
                case 0x0:
                    // return register X = Y
                    chip8->V[X] = chip8->V[Y];
                    break;
                case 0x1:
                    // return register X or Y
                    chip8->V[X] |= chip8->V[Y];
                    break;
                case 0x2:
                    // return register X and Y
                    chip8->V[X] &= chip8->V[Y];
                    break;
                case 0x3:
                    // return register X xor Y
                    chip8->V[X] ^= chip8->V[Y];
                    break;
                case 0x4:
                    // return register X + Y
                    chip8->V[X] += chip8->V[Y];
                    break;
                case 0x5: {
                    // mask the value for negative
                    uint8_t vX = chip8->V[X];
                    uint8_t vY = chip8->V[Y];
                    // if there is a borrow set to 0 else set to 1
                    chip8->V[N] = (vX >= vY);
                    // return register X - Y
                    chip8->V[X] = vX - vY;
                    break;
                }
                case 0x6: {
                    // store the last bit of register X
                    uint8_t last_bit = (chip8->V[X] & 0x1);
                    // check for the VY shifting quirk set in chip8 typedef
                    // if shift quirk is true: shift VX >> 1 and store to VX
                    // else: shift VY >> 1
                    if (chip8->vy_shift_quirk) {
                        chip8->V[X] = (chip8->V[X] >> 1);
                    } else {
                        chip8->V[X] = (chip8->V[Y] >> 1);
                    }
                    chip8->V[N] = last_bit;
                    break;
                }

                case 0x7: {
                    // mask the value for negative
                    uint8_t vX = chip8->V[X];
                    uint8_t vY = chip8->V[Y];
                    // if there is a borrow set to 0 else set to 1
                    chip8->V[N] = (vX >= vY);
                    // return register Y - X
                    chip8->V[X] = vY - vX;
                    break;
                }

                case 0xE: {
                    // Set VN to the most significant bit of VX
                    uint8_t first_bit = (chip8->V[X] & 0x80) >> 7;
                    // same check as OPCODE 0x6 for shifting quirk
                    if (chip8->vy_shift_quirk) {
                        chip8->V[X] = (chip8->V[X] << 1);
                    } else {
                        chip8->V[X] = (chip8->V[Y] << 1);
                    }
                    chip8->V[N] = first_bit;
                    break;
                }

                default:
                    printf("default");
            }
            break;
        case 0x9000:
            // 9XY0: If register X and Y are not equals
            if (chip8->V[X] != chip8->V[Y]) {
                chip8->pc += 2;
            }
            break;
        case 0xA000:
            // ANNN: Set the index register to the address NNN
            chip8->index_reg = NNN;
            break;
        case 0xB000:
            // BNNN: Jump to adress NNN + register 0
            chip8->pc = NNN + chip8->V[0];
            break;
        case 0xC000:
            // CXNN: Set register X to random number[0-255] AND NN
            chip8->V[X] = (rand() % 256) & NN;
            break;
        case 0xD000:
            // DXYN: Draw a sprite at coordinate VX, VY using N bytes of
            // sprite data starting at the address stored in the index
            // register if any set pixels are unset set VF to 1.
            // Otherwise, set VF to 0
            x = chip8->V[X];
            y = chip8->V[Y];
            chip8->V[0xF] = 0;

            for (int row = 0; row < N; row++) {
                int sprite = chip8->memory[chip8->index_reg + row];
                for (int col = 0; col < 8; col++) {
                    // mask the pixel and get its values by shifting

                    // todo change pixel declaration to: int pixel =
                    // (sprite >> (7 - col)) & 1;
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
        case 0xE000:
            switch (NN) {
                // EXA1: skip the next instruction if the key in
                // register X is not pressed
                case 0x9E:
                    if (chip8->keypad[chip8->V[X]] != 0) {
                        chip8->pc += 2;
                    }
                // EXA1: skip the next instruction if the key in
                // register X is not pressed
                case 0xA1:
                    if (chip8->keypad[chip8->V[X]] == 0) {
                        chip8->pc += 2;
                    }
            }
            break;
        case 0xF000:
            switch (NN) {
                    // set register to the valiue of delay_timer
                case 0x07:
                    chip8->V[X] = chip8->delay_timer;
                    break;
                    // wait for key press and store value in register X
                case 0x0A:
                    key_pressed = false;
                    for (int i = 0; i < 16; i++) {
                        if (chip8->keypad[i] == true) chip8->V[X] = i;
                        key_pressed = true;
                    }
                    if (!key_pressed) {
                        chip8->pc -= 2;
                    }
                    break;
                    // set delay timer to value of register X
                case 0x15:
                    chip8->delay_timer = chip8->V[X];
                    break;
                    // set sound timer to value of register X
                case 0x18:
                    chip8->sound_timer = chip8->V[X];
                    break;
                    // add value of register X to Index Register
                case 0x1E:
                    chip8->index_reg = chip8->index_reg + chip8->V[X];
                    break;
                case 0x29:
                    chip8->index_reg = chip8->V[X] * 5;
                    break;
                case 0x33:
                    chip8->memory[chip8->index_reg] = (chip8->V[X] / 100);
                    chip8->memory[chip8->index_reg + 1] =
                        ((chip8->V[X] / 10) % 10);
                    chip8->memory[chip8->index_reg + 2] = (chip8->V[X] % 10);
                    break;
                case 0x55:
                    for (int i = 0; i <= X; i++) {
                        chip8->memory[chip8->index_reg + i] = chip8->V[i];
                    }
                    chip8->index_reg =
                        chip8->index_reg + ((uint16_t)chip8->V[X]);
                    break;
                case 0x65:
                    for (int i = 0; i <= X; i++) {
                        chip8->V[i] = chip8->memory[chip8->index_reg + i];
                    }
                    chip8->index_reg =
                        chip8->index_reg + ((uint16_t)chip8->V[X] + 1);
                    break;
            }
            break;
        default:
            printf("error: unknown opcode 0x%04x\n", chip8->opcode & 0xF000);
            break;
    }
}

void chip8_load_rom(Chip8* chip8, const char* filename) {
    FILE* rom = fopen(filename, "rb");
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

// void chip8_opcode_debug(uint8_t* opcode) { printf("place holder"); }
