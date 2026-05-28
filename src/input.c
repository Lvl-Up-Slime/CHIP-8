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

void input_update(SDL_Event event, Input* input) {
    switch (event.type) {
        case SDL_EVENT_KEY_DOWN:
            switch (event.key.key) {
              case SDLK_1:
                  input->keypad[K_1] = 1; break;
              case SDLK_2:
                  input->keypad[K_2] = 1; break;
              case SDLK_3:
                  input->keypad[K_3] = 1; break;
              case SDLK_4:
                  input->keypad[K_C] = 1; break;
              case SDLK_Q:
                  input->keypad[K_4] = 1; break;
              case SDLK_W:
                  input->keypad[K_5] = 1; break;
              case SDLK_E:
                  input->keypad[K_6] = 1; break;
              case SDLK_R:
                  input->keypad[K_D] = 1; break;
              case SDLK_A:
                  input->keypad[K_7] = 1; break;
              case SDLK_S:
                  input->keypad[K_8] = 1; break;
              case SDLK_D:
                  input->keypad[K_9] = 1; break;
              case SDLK_F:
                  input->keypad[K_E] = 1; break;
              case SDLK_Z:
                  input->keypad[K_A] = 1; break;
              case SDLK_X:
                  input->keypad[K_0] = 1; break;
              case SDLK_C:
                  input->keypad[K_B] = 1;break;
              case SDLK_V:
                  input->keypad[K_F] = 1; break;
              default: break;
            }
            break;
        case SDL_EVENT_KEY_UP:
            switch (event.key.key) {
              case SDLK_1:
                  input->keypad[K_1] = 0; break;
              case SDLK_2:
                  input->keypad[K_2] = 0; break;
              case SDLK_3:
                  input->keypad[K_3] = 0; break;
              case SDLK_4:
                  input->keypad[K_C] = 0; break;
              case SDLK_Q:
                  input->keypad[K_4] = 0; break;
              case SDLK_W:
                  input->keypad[K_5] = 0; break;
              case SDLK_E:
                  input->keypad[K_6] = 0; break;
              case SDLK_R:
                  input->keypad[K_D] = 0; break;
              case SDLK_A:
                  input->keypad[K_7] = 0; break;
              case SDLK_S:
                  input->keypad[K_8] = 0; break;
              case SDLK_D:
                  input->keypad[K_9] = 0; break;
              case SDLK_F:
                  input->keypad[K_E] = 0; break;
              case SDLK_Z:
                  input->keypad[K_A] = 0; break;
              case SDLK_X:
                  input->keypad[K_0] = 0; break;
              case SDLK_C:
                  input->keypad[K_B] = 0; break;
              case SDLK_V:
                  input->keypad[K_F] = 0; break;
              default: break;
            }
            break;
    }
}


