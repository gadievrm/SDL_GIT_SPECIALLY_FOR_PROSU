#include <iostream>
#include "SoundAssetLoader.h"
#include "Audio.h"

EAssetType CSoundAssetLoader::getType() const {
    return ASSET_TYPE_SOUND;
}

bool CSoundAssetLoader::doesPathMatch(const std::string& path) const {
    // TODO: CHANGE
    return false;
}

ACAsset* CSoundAssetLoader::loadAsset(const std::string& path) {
    Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());

	std::cout << "CSoundAssetLoader::loadAsset(\"" << path << "\");" << std::endl;

    if (chunk != NULL)
        return new CSound(path, chunk);
    
    return NULL;
}