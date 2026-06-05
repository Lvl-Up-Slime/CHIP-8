#include "timer.h"
#include <SDL3/SDL.h>

void timer_init(Timer* timer) {
    timer->frame_start = 0;
    timer->frame_end = 0;
    timer->delay_timer = 0;
    timer->sound_timer = 0;

    timer->prev_timer = SDL_GetTicks(); //init timer
    timer->delay_timer = timer->delay_timer;
    timer->sound_timer = timer->sound_timer;
}

void frame_delay (Timer* timer) {
   uint32_t frame_time = timer->frame_end - timer->frame_start; 
    if (frame_time < FRAME_DURATION) {
        SDL_Delay(FRAME_DURATION - frame_time);
    };
}

void chip8_delay (Timer* timer) {
    if (timer->delay_timer > 0) {
        timer->delay_timer--;
    }

    if (timer->sound_timer > 0) { 
        // play sound
        timer->sound_timer--;
    }
}


