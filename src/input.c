#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <stdint.h>
#include "chip8.h"

void input_init(Chip8 * chip8) {
   for (int i = 0; i < 16; i++) {
      chip8->keypad[i] = 0;
   }
}

void input_update(SDL_Event event, Chip8 * chip8) {
    int value = 0;
    //checks if key is being pressed
    if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
         if (SDL_EVENT_KEY_DOWN == 1) {
             value = 1;
         }
         if (SDL_EVENT_KEY_DOWN == 0) {
             value = 0;
         }
    }

    switch (event.type) {
      case SDLK_1:
          chip8->keypad[0x1] = value;break;
      case SDLK_2:
          chip8->keypad[0x2] = value; break;
      case SDLK_3:
          chip8->keypad[0x3] = value; break;
      case SDLK_4:
          chip8->keypad[0xC] = value; break;
      case SDLK_Q:
          chip8->keypad[0x4] = value; break;
      case SDLK_W:
          chip8->keypad[0x5] = value; break;
      case SDLK_E:
          chip8->keypad[0x6] = value; break;
      case SDLK_R:
          chip8->keypad[0xD] = value; break;
      case SDLK_A:
          chip8->keypad[0x7] = value; break;
      case SDLK_S:
          chip8->keypad[0x8] = value; break;
      case SDLK_D:
          chip8->keypad[0x9] = value; break;
      case SDLK_F:
          chip8->keypad[0xE] = value; break;
      case SDLK_Z:
          chip8->keypad[0xA] = value; break;
      case SDLK_X:
          chip8->keypad[0x0] = value; break;
      case SDLK_C:
          chip8->keypad[0xB] = value; break;
      case SDLK_V:
          chip8->keypad[0xF] = value; break;
      default: break;
    }
}
