#include "AssetManager.h"
#include "Console.h"
namespace fs = std::filesystem;

void CAssetManager::addLoader(IAssetLoader &loader) {
    m_asset_loaders[int(loader.getType())] = &loader;
}

ACAsset* CAssetManager::fetchAsset(EAsset type, const std::filesystem::path& path) {
    ACAsset *asset;

    // TODO: Make the path unique
    fs::path unique_path = path;

    asset = m_assets[unique_path];

    if (asset == NULL) {
        gConsole.debug(std::string("[CAssetManager] loading ") + unique_path.string());
        asset = m_asset_loaders[int(type)]->loadAsset(*this, unique_path);
        m_assets[unique_path] = asset;
    }
    
    return asset;
}

CSound* CAssetManager::fetchSound(const std::filesystem::path& path) {
    return static_cast<CSound*>(fetchAsset(EAsset::Sound, fs::path("data/sfx") / path));
}

CImage* CAssetManager::fetchImage(const std::filesystem::path& path) {
    return static_cast<CImage*>(fetchAsset(EAsset::Image, fs::path("data/gfx") / path));
}

CAssetManager::CAssetManager() :
m_asset_loaders(int(EAsset::Count)) 
{}