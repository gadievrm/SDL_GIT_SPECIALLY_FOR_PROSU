#pragma once
#include <string>
#include <optional>
#include "Image.h"
#include "Asset.h"

class CTileset : public ACAsset {
private:
    const CImage &m_img;
    std::string m_name;
    int m_tile_size;
public:
    CTileset(std::optional<std::string> path, const CImage &image, const std::string& name, int tile_size);
    const std::string& getName() const;
    image_slice_t getTile(int tile);
    int getSize();
};