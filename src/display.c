#include "display.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <stdint.h>

void display_init(Display *display) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    exit(-1);
  }

  display->window =
      SDL_CreateWindow("chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       640, 320, 0x00000004);
}

void display_update(Display *display, const uint8_t video_buffer) {}

void display_destroy(Display *display) { SDL_Quit(); }
