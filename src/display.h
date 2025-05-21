#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdint.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
} Display;

void display_init(Display *display);
void display_update(Display *display, const uint8_t video_buffer);
void display_destroy(Display *display);

#endif //! DISPLAY_H
