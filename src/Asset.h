#pragma once
#include <string>
#include <optional>

enum EAssetType {
    ASSET_TYPE_SOUND,
    ASSET_TYPE_MUSIC,
    ASSET_TYPE_BITMAP,
    ASSET_TYPE_MAP,
    ASSET_TYPE_ANIMATION,
    ASSET_TYPE_COUNT
};

class ACAsset {
protected:
    EAssetType m_type;
    std::optional<std::string> m_path;
    
public:
    const EAssetType getType();
    const std::optional<std::string>& getPath();
};