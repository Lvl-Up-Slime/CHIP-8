#include "timer.h"
#include <SDL3/SDL.h>

void timer_init(Timer* timer) {
    timer->delay_timer = 0;
    timer->sound_timer = 0;

    timer->prev_timer = SDL_GetTicks(); //init timer
    timer->delay_timer = timer->delay_timer;
    timer->sound_timer = timer->sound_timer;
}
void timer_delay(Timer* timer) {
    timer->curr_timer = SDL_GetTicks();
    if (timer->prev_timer - timer->curr_timer > 16) {
        if (timer->delay_timer > 0){timer->delay_timer--;}
        if (timer->sound_timer > 0){timer->sound_timer--;}
    }
    timer->prev_timer = timer->curr_timer;
}
