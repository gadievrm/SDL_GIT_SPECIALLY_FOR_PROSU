#pragma once
#include <string>
#include <optional>
#include <filesystem>

enum class EAsset {
    Sound = 0,
    Music,
    Image,
    Map,
    Animation,
    Tileset,
    Count
};

class ACAsset {
protected:
    EAsset m_type;
    std::optional<std::filesystem::path> m_path;
    
public:
    const EAsset getType() const;
    const std::optional<std::filesystem::path>& getPath() const;
};