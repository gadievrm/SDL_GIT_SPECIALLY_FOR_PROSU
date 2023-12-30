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
    bool doesPathMatch(const std::filesystem::path& path) const override;
    ACAsset* loadAsset(CAssetManager &assets, const std::filesystem::path& path) override;
};