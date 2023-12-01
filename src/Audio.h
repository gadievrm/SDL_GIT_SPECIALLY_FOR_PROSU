#pragma once
#include <SDL2/SDL_mixer.h>

typedef Mix_Chunk sound_t;

class Audio {
private:
    Audio() = default;
public:
    static Audio *init();
    sound_t *loadSound(const char *path);
    void playSound(sound_t *sound);
};