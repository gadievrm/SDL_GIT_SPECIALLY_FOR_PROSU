#include "Audio.h"

CSound::CSound(std::optional<std::filesystem::path> path, Mix_Chunk *chunk) : m_chunk(chunk)
{
    m_type = EAsset::Sound;
    m_path = path;
}

Mix_Chunk* CSound::getChunk() {
    return m_chunk;
}

CAudio *CAudio::init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		return NULL;
	}

	Mix_AllocateChannels(32);

    Mix_MasterVolume(MIX_MAX_VOLUME / 3);

    CAudio *audio = new CAudio();

    return audio;
}

CSound *CAudio::loadSound(const std::filesystem::path& path) {
    CSound *sound = new CSound(path, Mix_LoadWAV(path.string().c_str()));
    return sound;
}

void CAudio::playSound(CSound *sound) {
    Mix_PlayChannel(-1, sound->getChunk(), 0);
}