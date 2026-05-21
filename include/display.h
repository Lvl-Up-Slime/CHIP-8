#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL3/SDL.h>

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

typedef struct {
  SDL_Window * window;
  SDL_Renderer * renderer;
  SDL_Texture * texture;
  int window_scale;
  bool draw_flag;
  uint8_t video[SCREEN_WIDTH * SCREEN_HEIGHT];  
} Display;

void display_init(Display * display);
void display_update(Display * display);
void display_destroy(Display * display);

#endif //! DISPLAY_H
