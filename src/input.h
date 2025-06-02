#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <stdint.h>

typedef struct {
  uint8_t *keys[16];
} Input;

// change this to the chip8->keypad
void input_init(const uint8_t keypad[16]);
void sdl_input_request(SDL_Keycode key);

#endif //! INPUT_H
