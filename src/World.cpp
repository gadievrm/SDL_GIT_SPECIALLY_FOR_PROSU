#include <cmath>
#include "World.h"

CWorld::CWorld(CTileset &tileset, CImage& background, uint16_t width, uint16_t height) :
m_tileset(tileset),
m_background(background),
m_width(width),
m_height(height),
m_tiles(width*height)
{}

void CWorld::putTiles(const std::vector<uint16_t>& tiles) {
    m_tiles.assign(tiles.begin(), tiles.end());
}

void CWorld::init(TGameSystems systems) {
    // No init (for now)
}

void CWorld::logic(double dt) {
    // No logic (for now)
}

void CWorld::draw(CGraphics *graphics) {
    graphics->drawImageFullscreen(&m_background);

    int sz = m_tileset.getSize();
    for (int i = 0; i < m_width * m_height; i++) {
        int x = (i % m_width) * sz;
        int y = (i / m_width) * sz;

        graphics->drawImageSlice(m_tileset.getTileImageSlice(m_tiles[i]), x, y, false);
    }
}

#include <iostream>

std::optional<ETileMaterial> CWorld::getTileMaterialAt(float x, float y) {
    int tile_size = m_tileset.getSize();
    int tileX = int(x) / tile_size - int(x >= -tile_size && x < 0.0);
    int tileY = int(y) / tile_size - int(y >= -tile_size && y < 0.0);

    if (tileX < 0 || tileX >= m_width) return std::nullopt;
    if (tileY < 0 || tileY >= m_height) return std::nullopt;

    int tileID = tileX + tileY * m_width;

    return m_tileset.getMaterial(m_tiles[tileID]);
}