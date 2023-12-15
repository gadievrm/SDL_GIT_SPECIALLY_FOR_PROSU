#pragma once
#include "Asset.h"
#include "AssetLoader.h"

class CSoundAssetLoader : public IAssetLoader {
public:
    CSoundAssetLoader() = default;
    EAssetType getType() const override;
    bool doesPathMatch(const std::string& path) const override;
    ACAsset* loadAsset(const std::string& path) override;
};