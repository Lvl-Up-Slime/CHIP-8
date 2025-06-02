#include "input.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <stdint.h>

void input_init(const uint8_t keyPad[16]) {}

void sdl_input_request(SDL_Keycode key) {
  switch (key) {
  case SDLK_1:
    0x10;
  case SDLK_2:
    0x20;
  case SDLK_3:
    0x30;
  case SDLK_4:
    0xC0;
  case SDLK_q:
    0x40;
  case SDLK_w:
    0x50;
  case SDLK_e:
    0x60;
  case SDLK_r:
    0xD0;
  case SDLK_a:
    0x70;
  case SDLK_s:
    0x80;
  case SDLK_d:
    0x90;
  case SDLK_f:
    0xE0;
  case SDLK_z:
    0xA0;
  case SDLK_x:
    0x00;
  case SDLK_c:
    0xB0;
  case SDLK_v:
    0xF0;
  }
}
