#pragma once
#include <string>
#include <optional>

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
    std::optional<std::string> m_path;
    
public:
    const EAsset getType();
    const std::optional<std::string>& getPath();
};