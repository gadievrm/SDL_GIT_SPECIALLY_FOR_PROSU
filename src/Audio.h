#pragma once
#include <SDL_mixer.h>
#include <string>
#include "Asset.h"

class CAudio;
class CSound : public ACAsset {
private:
    Mix_Chunk *m_chunk;
public:
    CSound(std::optional<std::filesystem::path>, Mix_Chunk *chunk);
    Mix_Chunk *getChunk();
};

class CAudio {
private:
    CAudio() = default;
public:
    static CAudio *init();
    CSound *loadSound(const std::filesystem::path& path);
    void playSound(CSound *sound);
};