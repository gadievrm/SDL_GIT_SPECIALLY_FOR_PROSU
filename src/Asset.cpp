#include "Asset.h"

const EAsset ACAsset::getType() const {
    return m_type;
}

const std::optional<std::filesystem::path>& ACAsset::getPath() const {
    return m_path;
}