#pragma once
#include <SDL.h>
#include "Asset.h"
#include "AssetLoader.h"

class CTilesetAssetLoader : public IAssetLoader {
private:
    SDL_Renderer *m_renderer;
public:
    CTilesetAssetLoader(SDL_Renderer *renderer);
    EAsset getType() const override;
    bool doesPathMatch(const std::string& path) const override;
    ACAsset* loadAsset(CAssetManager &assets, const std::string& path) override;
};