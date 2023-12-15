#include "AssetManager.h"

void CAssetManager::addLoader(IAssetLoader &loader) {
    m_asset_loaders[int(loader.getType())] = &loader;
}

ACAsset* CAssetManager::fetchAsset(EAssetType type, const std::string& path) {
    ACAsset *asset;

    asset = m_assets[path];

    if (asset == NULL) {
        asset = m_asset_loaders[int(type)]->loadAsset(path);
        m_assets[path] = asset;
    }
    
    return asset;
}

CAssetManager::CAssetManager() :
m_asset_loaders(ASSET_TYPE_COUNT) 
{}