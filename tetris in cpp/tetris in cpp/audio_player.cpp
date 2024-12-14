#include "audio_player.h"
#include <SDL.h>
#include <iostream>

static Uint32 wav_length; // length of our sample
static Uint8 *wave_start;
static SDL_AudioSpec wav_spec; // the specs of our piece of music
SDL_AudioDeviceID device;

std::string file_path = R"(.\Assets\Sounds\bgm2.wav)";

void audio_player::init() {
    wav_spec.samples = 44100;
    wav_spec.freq = 1000;
    wav_spec.channels = 2;
    if (SDL_LoadWAV(file_path.c_str(), &wav_spec, &wave_start, &wav_length) == nullptr) {//make sure to unload or free the file in the de-constructor
        std::cout << "can not load audio file";
        return;
    }
}

void audio_player::setup_device() {
    device = SDL_OpenAudioDevice(nullptr, 0, &wav_spec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (device == 0) {
        std::cerr << "sound device error: " << SDL_GetError() << std::endl;
    }
}

void audio_player::play_bgm() {
    int status = SDL_QueueAudio(device, wave_start, wav_length);
    SDL_PauseAudioDevice(device, 0);
}
