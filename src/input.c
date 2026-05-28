#include <SDL3/SDL.h>
#include "input.h"

void input_init(Input* input) {
    memset(input->keypad, 0, sizeof(input->keypad));

   for (int i = 0; i < 16; i++) {
      input->keypad[i] = 0;
   }
}

uint8_t input_event_check (Input* input, uint8_t key) {
    switch (key){
      case 0x1:
          return input->keypad[K_1];
      case 0x2:
          return input->keypad[K_2];
      case 0x3:
          return input->keypad[K_3];
      case 0xC:
          return input->keypad[K_C];
      case 0x4:
          return input->keypad[K_4];
      case 0x5:
          return input->keypad[K_5];
      case 0x6:
          return input->keypad[K_6];
      case 0xD:
          return input->keypad[K_D];
      case 0x7:
          return input->keypad[K_7];
      case 0x8:
          return input->keypad[K_8];
      case 0x9:
          return input->keypad[K_9];
      case 0xE:
          return input->keypad[K_E];
      case 0xA:
          return input->keypad[K_A];
      case 0x0:
          return input->keypad[K_0];
      case 0xB:
          return input->keypad[K_B];
      case 0xF:
          return input->keypad[K_F];
      default: 
          return -1;
    };
};

void static which_key(Input* input, SDL_Keycode key, int value) {
    switch (key) {
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

void input_update(SDL_Event event, Input* input) {
    switch (event.type) {
        case SDL_EVENT_KEY_DOWN:
            which_key(input, event.key.key, 1);
            break;
        case SDL_EVENT_KEY_UP:
            which_key(input, event.key.key, 0);
            break;
    }
}


