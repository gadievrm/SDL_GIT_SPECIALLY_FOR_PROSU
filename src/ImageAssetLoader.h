#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "AssetLoader.h"
#include "Image.h"

class CImageAssetLoader : public IAssetLoader {
private:
    SDL_Renderer *m_renderer;
public:
    CImageAssetLoader(SDL_Renderer *renderer);
    EAsset getType() const override;
    bool doesPathMatch(const std::filesystem::path& path) const override;
    ACAsset* loadAsset(CAssetManager &assets, const std::filesystem::path& path) override;
};