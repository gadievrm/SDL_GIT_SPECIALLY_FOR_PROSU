#pragma once
#include "Asset.h"
#include "AssetLoader.h"

class CSoundAssetLoader : public IAssetLoader {
public:
    CSoundAssetLoader() = default;
    EAsset getType() const override;
    bool doesPathMatch(const std::filesystem::path& path) const override;
    ACAsset* loadAsset(CAssetManager &assets, const std::filesystem::path& path) override;
};