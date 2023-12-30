#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "Asset.h"
#include "Audio.h"
#include "Image.h"

class CAssetManager;
class IAssetLoader;
#include "AssetLoader.h"

class CAssetManager {
private:
    std::vector<ACAsset*> m_untagged_assets;
    std::unordered_map<std::filesystem::path, ACAsset*> m_assets;
    std::vector<IAssetLoader*> m_asset_loaders;
public:
    CAssetManager();
    void addLoader(IAssetLoader &loader);
    ACAsset* fetchAsset(EAsset type, const std::filesystem::path &path);
    CImage* fetchImage(const std::filesystem::path &path);
    CSound* fetchSound(const std::filesystem::path &path);
};