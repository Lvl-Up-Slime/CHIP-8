#ifndef DISPLAY_H
#define DISPLAY_H

#include "chip8.h"
#include <SDL3/SDL.h>

typedef struct {
  SDL_Window * window;
  SDL_Renderer * renderer;
  SDL_Texture * texture;
  int window_scale;
} Display;

void display_init(Display * display);
void display_update(Display * display, Chip8 * chip8);
void display_destroy(Display * display);

#endif //! DISPLAY_H
