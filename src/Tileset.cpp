#include "Tileset.h"

CTileset::CTileset(std::optional<std::string> path, const CImage &image, const std::string& name, int tile_size) :
m_img(image),
m_name(name),
m_tile_size(tile_size) 
{
    m_type = EAsset::Tileset;
    m_path = path;
}

const std::string& CTileset::getName() const {
    return m_name;
}

image_slice_t CTileset::getTile(int tile) {
    int tsw = m_img.getWidth();
    int sz = m_tile_size;
    int n_x = tsw / sz;

    int x = (tile % n_x) * sz;
    int y = (tile / n_x) * sz;

    return image_slice_t {.image = m_img, .x = x, .y = y, .w = sz, .h = sz};
}

int CTileset::getSize() {
    return m_tile_size;
}