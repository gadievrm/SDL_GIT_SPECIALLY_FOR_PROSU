#include "Asset.h"

const EAssetType ACAsset::getType() {
    return m_type;
}

const std::optional<std::string>& ACAsset::getPath() {
    return m_path;
}