#include <SDL3/SDL.h>
#include "input.h"

void input_init(Input* input) {
    memset(input->keypad, 0, sizeof(input->keypad));

   for (int i = 0; i < 16; i++) {
      input->keypad[i] = 0;
   }
}

void input_update(SDL_Event event, Input* input) {
    int value = 0;
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
          input->keypad[K_1] = value; break;
      case SDLK_2:
          input->keypad[K_2] = value; break;
      case SDLK_3:
          input->keypad[K_3] = value; break;
      case SDLK_4:
          input->keypad[K_C] = value; break;
      case SDLK_Q:
          input->keypad[K_4] = value; break;
      case SDLK_W:
          input->keypad[K_5] = value; break;
      case SDLK_E:
          input->keypad[K_6] = value; break;
      case SDLK_R:
          input->keypad[K_D] = value; break;
      case SDLK_A:
          input->keypad[K_7] = value; break;
      case SDLK_S:
          input->keypad[K_8] = value; break;
      case SDLK_D:
          input->keypad[K_9] = value; break;
      case SDLK_F:
          input->keypad[K_E] = value; break;
      case SDLK_Z:
          input->keypad[K_A] = value; break;
      case SDLK_X:
          input->keypad[K_0] = value; break;
      case SDLK_C:
          input->keypad[K_B] = value; break;
      case SDLK_V:
          input->keypad[K_F] = value; break;
      default: break;
    }
}
