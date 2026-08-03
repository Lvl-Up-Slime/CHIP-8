#ifndef AUDIO_H
#define AUDIO_H

#include <SDL3/SDL.h>

typedef struct {
    SDL_AudioStream *stream;
    SDL_AudioSpec spec;

    float freq;
    float phase;
    bool is_playing;
} Audio;

void audio_init(Audio* audio, SDL_AudioFormat format, int channels, int freq);
float audio_generate_square_phase(Audio *audio);
void audio_callback(void *data, SDL_AudioStream *stream, int additional_size, int total_size);
#endif 
