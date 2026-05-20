#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include "SDL3/SDL_init.h"
#include "chip8.h"
#include "display.h"
#include "input.h"
#include "timer.h"

// declare struct and variables
volatile bool running = true;
Chip8 chip8;
Display display;
Timer timer;

int main(int argc, char* argv[]) {
    // input validation
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <Shift Flag> <ROM file>\n", argv[0]);
        return 1;
    } 

    int index_of_file = 0;
    if (argc == 2) {
        index_of_file = 1;
    }else if (argc == 3) {
        index_of_file = 2;
    };

    //vy_shift_quirk
    bool vy_shift_quirk = false;
    for (int i = 0; i < argc; i++) {
      if (strcmp(argv[i], "--shift-quirk=modern")) {
        vy_shift_quirk = true; 
      } else if (strcmp(argv[i], "--shift-quirk=original")) {
        vy_shift_quirk = false; 
      } 
    };
    
    const char* filename = argv[index_of_file]; 

    // init systems
    chip8_init(&chip8);
    display_init(&display);
    input_init(&chip8);
    timer_init(&timer, &chip8);

    chip8_load_rom(&chip8, filename);  // load rom
    
    chip8.vy_shift_quirk = vy_shift_quirk;

    // main emulator loop
    while (running) {
        SDL_Event event;  // keyboard events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                SDL_Quit();
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
