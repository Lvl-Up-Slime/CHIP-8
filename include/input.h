#ifndef INPUT_H
#define INPUT_H
#include <SDL3/SDL.h>

typedef struct {
    uint8_t keypad[16];  // 16-key input
} Input;

enum keypad {
   K_1,K_2,K_3,K_C,
   K_4,K_5,K_6,K_D,
   K_7,K_8,K_9,K_E,
   K_A,K_0,K_B,K_F
};

void input_init(Input* input);

void input_update(SDL_Event event, Input* input);

#endif //INPUT_H
