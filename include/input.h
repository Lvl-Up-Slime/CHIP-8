#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <SDL3/SDL.h>

void input_init(Chip8 * chip8);

void input_update(SDL_Event event, Chip8 * chip8);

#endif //INPUT_H
