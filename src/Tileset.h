#pragma once
#include <string>
#include <optional>
#include <vector>
#include <cstring>
#include "Image.h"
#include "Asset.h"

enum class ETileMaterial {
    None = 0,
    Basic,
    Stone,
    Water,
    Sand,
    Dirt,
    Wood,
    Panel,
    COUNT
};

inline const char* TileMaterialToString(ETileMaterial mat) {
    switch (mat) {
        case ETileMaterial::None:
            return "none";
        case ETileMaterial::Basic:
            return "basic";
        case ETileMaterial::Stone:
            return "stone";
        case ETileMaterial::Water:
            return "water";
        case ETileMaterial::Sand:
            return "sand";
        case ETileMaterial::Dirt:
            return "dirt";
        case ETileMaterial::Wood:
            return "wood";
        case ETileMaterial::Panel:
            return "panel";
    }

    return "";
}

inline ETileMaterial StringToTileMaterial(const char* str) {
    if (strnicmp(str, "none", 4) == 0) {
        return ETileMaterial::None;
    } else if (strnicmp(str, "basic", 5) == 0) {
        return ETileMaterial::Basic;
    } else if (strnicmp(str, "stone", 5) == 0) {
        return ETileMaterial::Stone;
    } else if (strnicmp(str, "water", 5) == 0) {
        return ETileMaterial::Water;
    } else if (strnicmp(str, "sand", 4) == 0) {
        return ETileMaterial::Sand;
    } else if (strnicmp(str, "dirt", 4) == 0) {
        return ETileMaterial::Dirt;
    } else if (strnicmp(str, "wood", 4) == 0) {
        return ETileMaterial::Wood;
    } else if (strnicmp(str, "panel", 4) == 0) {
        return ETileMaterial::Panel;
    }

    return ETileMaterial::None;
}

class CTileset : public ACAsset {
private:
    CImage *m_img;
    std::string m_name;
    int m_tile_size;
    std::vector<ETileMaterial> m_materials;
public:
    CTileset(std::optional<std::filesystem::path> path, const CImage &image, const std::string& name, int tile_size);

    const std::string& getName() const;
    image_islice_t getTileImageSlice(int tile);
    image_fslice_t getTileImageSliceNormalized(int tile);
    int getTileSize();
    int getSize();
    void setMaterial(int tile, ETileMaterial material);
    std::optional<ETileMaterial> getMaterial(int tile);
    const std::vector<ETileMaterial>& getAllMaterials();
};