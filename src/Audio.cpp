#include "Audio.h"

Audio *Audio::init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		return NULL;
	}

	Mix_AllocateChannels(32);

    Audio *audio = new Audio();

    return audio;
}

sound_t *Audio::loadSound(const char *path) {
    return (sound_t*) Mix_LoadWAV(path);
}

void Audio::playSound(sound_t *sound) {
    Mix_PlayChannel(-1, (Mix_Chunk*) sound, 0);;
}