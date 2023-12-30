#include "Tileset.h"

CTileset::CTileset(std::optional<std::filesystem::path> path, const CImage &image, const std::string& name, int tile_size) :
m_img(&(const_cast<CImage&>(image))),
m_name(name),
m_tile_size(tile_size),
m_materials(
    (image.getWidth() / tile_size) * (image.getHeight() / tile_size) 
)
{
    m_type = EAsset::Tileset;
    m_path = path;
}

const std::string& CTileset::getName() const {
    return m_name;
}

image_islice_t CTileset::getTileImageSlice(int tile) {
    int tsw = m_img->getWidth();
    int sz = m_tile_size;
    int n_x = tsw / sz;

    int x = (tile % n_x) * sz;
    int y = (tile / n_x) * sz;

    return image_islice_t {
        .image = *m_img, 
        .x = x, 
        .y = y, 
        .w = sz, 
        .h = sz
    };
}

image_fslice_t CTileset::getTileImageSliceNormalized(int tile) {
    int tsw = m_img->getWidth();
    int tsh = m_img->getHeight();
    int sz = m_tile_size;
    int n_x = tsw / sz;

    int x = (tile % n_x) * sz;
    int y = (tile / n_x) * sz;

    return image_fslice_t {
        .image = *m_img, 
        .x = ((float) x)  / tsw, 
        .y = ((float) y)  / tsh, 
        .w = ((float) sz) / tsw, 
        .h = ((float) sz) / tsh
    };
}

int CTileset::getSize() {
    return m_materials.size();
}

int CTileset::getTileSize() {
    return m_tile_size;
}

void CTileset::setMaterial(int tile, ETileMaterial material) {
    m_materials[tile] = material;
}

std::optional<ETileMaterial> CTileset::getMaterial(int tile) {
    if (tile < 0 || tile >= m_materials.size()) return std::nullopt;

    return m_materials[tile];
}

const std::vector<ETileMaterial>& CTileset::getAllMaterials() {
    return m_materials;
}