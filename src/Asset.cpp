#include "Asset.h"

const EAsset ACAsset::getType() {
    return m_type;
}

const std::optional<std::string>& ACAsset::getPath() {
    return m_path;
}