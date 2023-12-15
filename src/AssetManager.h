#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Asset.h"
#include "AssetLoader.h"

class CAssetManager {
private:
    std::vector<ACAsset*> m_untagged_assets;
    std::unordered_map<std::string, ACAsset*> m_assets;
    std::vector<IAssetLoader*> m_asset_loaders;
public:
    CAssetManager();
    void addLoader(IAssetLoader &loader);
    ACAsset* fetchAsset(EAssetType type, const std::string &path);
};