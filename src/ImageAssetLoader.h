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
    EAssetType getType() const override;
    bool doesPathMatch(const std::string& path) const override;
    ACAsset* loadAsset(const std::string& path) override;
};