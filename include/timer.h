#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

#define INSTRUCTION_PER_FRAME 9 
#define FPS 60
#define FRAME_DURATION (1000 / FPS)

typedef struct {
    uint32_t frame_start;
    uint32_t frame_end;

    uint8_t delay_timer;
    uint8_t sound_timer;
    uint32_t prev_timer;
    uint32_t curr_timer;
} Timer;

void timer_init(Timer * timer);
void frame_delay(Timer * timer);
void chip8_delay(Timer * timer);
#endif //TIMER_H
