#include "AssetManager.h"

void CAssetManager::addLoader(IAssetLoader &loader) {
    m_asset_loaders[int(loader.getType())] = &loader;
}

ACAsset* CAssetManager::fetchAsset(EAsset type, const std::string& path) {
    ACAsset *asset;

    // TODO: Make the path unique
    std::string unique_path = path;

    asset = m_assets[unique_path];

    if (asset == NULL) {
        asset = m_asset_loaders[int(type)]->loadAsset(*this, unique_path);
        m_assets[unique_path] = asset;
    }
    
    return asset;
}

CSound* CAssetManager::fetchSound(const std::string& path) {
    return static_cast<CSound*>(fetchAsset(EAsset::Sound, std::string("data/sfx/").append(path)));
}

CImage* CAssetManager::fetchImage(const std::string& path) {
    return static_cast<CImage*>(fetchAsset(EAsset::Image, std::string("data/gfx/").append(path)));
}

CAssetManager::CAssetManager() :
m_asset_loaders(int(EAsset::Count)) 
{}