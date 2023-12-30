#include <iostream>
#include "SoundAssetLoader.h"
#include "Audio.h"

EAsset CSoundAssetLoader::getType() const {
    return EAsset::Sound;
}

bool CSoundAssetLoader::doesPathMatch(const std::filesystem::path& path) const {
    // TODO: CHANGE
    return false;
}

ACAsset* CSoundAssetLoader::loadAsset(CAssetManager &assets, const std::filesystem::path& path) {
    Mix_Chunk *chunk = Mix_LoadWAV(path.string().c_str());

	// std::cout << "CSoundAssetLoader::loadAsset(\"" << path << "\");" << std::endl;

    if (chunk != NULL)
        return new CSound(path, chunk);
    
    return NULL;
}