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
    bool doesPathMatch(const std::string& path) const override;
    ACAsset* loadAsset(CAssetManager &assets, const std::string& path) override;
};