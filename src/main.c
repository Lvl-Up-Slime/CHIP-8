#include <SDL3/SDL.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "chip8.h"
#include "display.h"
#include "input.h"
#include "timer.h"

// declare struct and variables
volatile bool running = true;
Chip8 chip8;
Display display;
Timer timer;
void handle_sigint(int sig) { running = false; }

// "!cd ../; make run"
int main(int argc, char *argv[]) {
    signal(SIGINT, handle_sigint);  // enables Ctrl+c shutdown

    // input validation
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <ROM file>\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];

    // init systems
    chip8_init(&chip8);
    display_init(&display);
    input_init(&chip8);
    timer_init(&timer, &chip8);
    
    //need to implement shift quirk validation: vy_shift_quirk


    chip8_load_rom(&chip8, filename);  // load rom

    // main emulator loop
    while (running) {
        SDL_Event event;  // keyboard events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            input_update(event, &chip8);
        }

        chip8_emulate_cycles(&chip8);  // execute one opcode

        timer_delay(&timer);  // delay/sound timer

        if (chip8.draw_flag) {  // draws to SDL window
            display_update(&display, &chip8);
            chip8.draw_flag = false;
        }
        SDL_Delay(16);  //-60 fps
    }
    return 0;
}

