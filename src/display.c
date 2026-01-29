#include "display.h"

#include <SDL3/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "SDL3/SDL_init.h"

void display_init(Display* display) {
    display->window_scale = 10;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != true) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    display->window = SDL_CreateWindow("chip8", 64 * display->window_scale,
                                       32 * display->window_scale, 0);
    if (display->window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        exit(-1);
    }

    display->renderer = SDL_CreateRenderer(display->window, NULL);
    if (display->renderer == NULL) {
        printf("SDL_CreateRenderer Failed Error: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
    SDL_RenderClear(display->renderer);
    SDL_RenderPresent(display->renderer);
}

void display_update(Display* display, Chip8* chip8) {
    SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
    SDL_RenderClear(display->renderer);

    // iterates through a width x height grid
    for (int row = 0; row < SCREEN_HEIGHT; row++) {
        for (int col = 0; col < SCREEN_WIDTH; col++) {
            int index = row * 64 + col;
            // if pixel is white
            if (chip8->video[index] == 1) {
                SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 255);
                // else pixel is black
            } else {
                continue;
            }
            // scales window to become larger
            SDL_FRect pixel_rect = {
                col * display->window_scale, row * display->window_scale,
                display->window_scale, display->window_scale};
            SDL_RenderFillRect(display->renderer, &pixel_rect);
        }
    }
    // renders to the screen
    SDL_RenderPresent(display->renderer);
}

// void display_destroy(Display* display) { SDL_Quit(); }
