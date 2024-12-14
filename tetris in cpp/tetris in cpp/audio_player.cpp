#include "audio_player.h"
#include <SDL.h>
#include <iostream>
#include "SDL_mixer.h"

SDL_AudioDeviceID device;

Mix_Music* bg_music;

audio_player::~audio_player()
{
    Mix_FreeMusic(bg_music);
    bg_music = nullptr;
}


void audio_player::init() {
  

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    bg_music = Mix_LoadMUS(R"(.\Assets\Sounds\bgm2.wav)");
    if (bg_music == nullptr)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }
}

void audio_player::play_bgm() {
   
    Mix_PlayMusic(bg_music, -1);
}

/*
	-not using mixer-

    static Uint32 wav_length; // length of our sample
    static Uint8 *wave_start;
    static SDL_AudioSpec wav_spec; // the specs of our piece of music

	auto loaded = SDL_LoadWAV(file_path.c_str(), &wav_spec, &wave_start, &wav_length);
    if (loaded == nullptr) {//make sure to unload or free the file in the de-constructor
        std::cout << "can not load audio file";
        return;
    }

    device = SDL_OpenAudioDevice(nullptr, 0, &wav_spec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (device == 0) {
        std::cerr << "sound device error: " << SDL_GetError() << std::endl;
    }
    
    int status = SDL_QueueAudio(device, wave_start, wav_length);
	SDL_PauseAudioDevice(device, 0);

 */