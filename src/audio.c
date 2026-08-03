#include <SDL3/SDL.h>
#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
void audio_callback(void *userdata, SDL_AudioStream *stream, int additional_size, int total_size);

void audio_init(Audio* audio, SDL_AudioFormat format, int channels, int sample_rate){
    SDL_AudioSpec spec = {
        .format = format,
        .channels = channels,
        .freq = sample_rate
    };
    audio->freq = 440;

    audio->stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, audio_callback, audio);
    if (audio->stream == NULL) {
        printf("SDL_OpenAudioDeviceStream Error: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_ResumeAudioStreamDevice(audio->stream);
}

float audio_generate_square_phase(Audio *audio){
    float sample = 0.0f;

    if (audio->phase < 0.5f){
        sample = 0.5f;
    } else {
        sample = -0.5f;
    }
    // one sample = (square_frequency) / (sample_rate)
    audio->phase += audio->freq / audio->spec.freq; 

    if (audio->phase >= 1.0f){
        audio->phase -= 1.0f;
    }

    return sample;
}

void audio_callback(void *data, SDL_AudioStream *stream, int additional_size, int total_size){
    Audio *audio = data;

    int samples = additional_size / sizeof(float);

    float *buffer = malloc(additional_size);
    
    for (int i = 0; i < samples; i++){
        if (audio->is_playing){
            buffer[i] = audio_generate_square_phase(audio);
        } else {
            buffer[i] = 0.0f; 
        }
    }

    SDL_PutAudioStreamData(stream, buffer, additional_size);

    free(buffer);
};

