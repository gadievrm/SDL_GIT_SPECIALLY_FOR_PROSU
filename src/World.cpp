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

void CWorld::logic(double dt) {
    // No logic (for now)
}

void CWorld::draw(CGraphics *graphics) {
    graphics->drawImageFullscreen(&m_background);

    int sz = m_tileset.getSize();
    for (int i = 0; i < m_width * m_height; i++) {
        int x = (i % m_width) * sz;
        int y = (i / m_width) * sz;

        graphics->drawImageSlice(m_tileset.getTile(m_tiles[i]), x, y, false);
    }
}