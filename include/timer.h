#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

typedef struct {
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint32_t prev_timer;
    uint32_t curr_timer;
} Timer;

void timer_init(Timer * timer);
void timer_delay(Timer * timer);
#endif //TIMER_H
