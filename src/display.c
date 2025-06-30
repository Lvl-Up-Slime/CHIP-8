#include "display.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <stdint.h>

void display_init(Display * display) {
  display->window_scale = 20;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    exit(-1);
  }

  display->window = SDL_CreateWindow(
      "chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      64 * display->window_scale, 32 * display->window_scale, SDL_WINDOW_SHOWN);

  display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
    SDL_RenderClear(display->renderer);
    SDL_RenderPresent(display->renderer);

}

void display_update(Display * display, Chip8 * chip8) {
  SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
  SDL_RenderClear(display->renderer);

  // iterates through a width x height grid
  for (int row = 0; row < 32; row++) {
    for (int col = 0; col < 64; col++) {
      int index = row * 64 + col;
      // if pixel is white
      if (chip8->video[index] == 1) {
        SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 255);
      // else pixel is black
      } else {
        SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
      }
      // scales window to become larger
      SDL_Rect pixel_rect = {col * display->window_scale,
                             row * display->window_scale, display->window_scale,
                             display->window_scale};
      SDL_RenderFillRect(display->renderer, &pixel_rect);
    }
  }
  // renders to the screen
  SDL_RenderPresent(display->renderer);
}

void display_destroy(Display *display) { SDL_Quit(); }
