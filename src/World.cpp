#include <cmath>
#include "World.h"

CWorld::CWorld(CTileset &tileset, CImage& background, uint16_t width, uint16_t height) :
ACEntity(CWorld::CLASS_NAME),
m_tileset(&tileset),
m_background(background),
m_width(width),
m_height(height),
m_tiles(width*height)
{}

CWorld CWorld::makeDefault(CAssetManager& assets) {
    CTileset* tileset = static_cast<CTileset*>(assets.fetchAsset(EAsset::Tileset, "data/gfx/env/tilesets/aztec.json"));
    CImage* bg = assets.fetchImage("env/bg/back.png");
    return CWorld(*tileset, *bg, 20, 20);
}

uint16_t CWorld::getWidth() {
    return m_width;
}

uint16_t CWorld::getHeight() {
    return m_height;
}

void_sex CWorld::resize(uint16_t new_width, uint16_t new_height, bool copy_tiles) {
    std::vector<uint16_t> new_tiles(new_width * new_height, 0);

    if (copy_tiles) {
        for (int y = 0; y < std::min(m_height, new_height); y++) {
            for (int x = 0; x < std::min(m_width, new_width); x++) {
                new_tiles[x + y * new_width] = m_tiles[x + y * m_width];
            }
        }
        m_tiles = new_tiles;
    }

    m_width = new_width;
    m_height = new_height;
}

void_sex CWorld::changeBackgroundImage(CImage& new_background_image) {
    m_background = new_background_image;
}

CImage& CWorld::getBackgroundImage() {
    return m_background;
}

void_sex CWorld::putTiles(const std::vector<uint16_t>& tiles) {
    m_tiles.assign(tiles.begin(), tiles.end());
}

void_sex CWorld::init(TGameSystems systems) {
    // No init (for now)
}

void_sex CWorld::logic(double dt) {
    // No logic (for now)
    // static double wtime = 0.0;
    // wtime += dt;
    // float dist = 800 * sin(wtime / 80000);
    // setPosX(cos(wtime / 7200.0) * dist);
    // setPosY(sin(wtime / 7200.0) * dist);
}

void_sex CWorld::draw(CGraphics *graphics) {
    float offX = getPosX();
    float offY = getPosY();
    graphics->drawImageFullscreen(&m_background);

    int sz = m_tileset->getTileSize();
    for (int i = 0; i < m_width * m_height; i++) {
        int x = (i % m_width) * sz;
        int y = (i / m_width) * sz;

        graphics->drawImageSlice(m_tileset->getTileImageSlice(m_tiles[i]), offX + x, offY + y, false);
    }
}

void_sex CWorld::convertToTileCoords(int &x, int &y) {
    int sz = m_tileset->getTileSize();
    x = int(x - getPosX()) / sz;
    y = int(y - getPosY()) / sz;
}

void_sex CWorld::drawTileInWorld(CGraphics *graphics, int tile, int x, int y) {
    int sz = m_tileset->getTileSize();
    graphics->drawImageSlice(m_tileset->getTileImageSlice(tile), getPosX() + x * sz, getPosY() + y * sz, false);
}

void_sex CWorld::setTile(int x, int y, int tile) {
    if (x < 0 || x >= m_width) return;
    if (y < 0 || y >= m_height) return;
    m_tiles[x + y * m_width] = tile;
}

std::optional<int> CWorld::getTile(int x, int y) {
    if (x < 0 || x >= m_width)  return std::nullopt;
    if (y < 0 || y >= m_height) return std::nullopt;
    return m_tiles[x + y * m_width];
}

std::vector<uint16_t>& CWorld::getAllTiles() {
    return m_tiles;
}

int CWorld::getTileSize() {
    return m_tileset->getTileSize();
}

std::optional<ETileMaterial> CWorld::getTileMaterialAt(float x, float y) {
    x -= getPosX();
    y -= getPosY();
    int tile_size = m_tileset->getTileSize();
    int tileX = int(x) / tile_size - int(x >= -tile_size && x < 0.0);
    int tileY = int(y) / tile_size - int(y >= -tile_size && y < 0.0);

    if (tileX < 0 || tileX >= m_width) return std::nullopt;
    if (tileY < 0 || tileY >= m_height) return std::nullopt;

    int tileID = tileX + tileY * m_width;

    return m_tileset->getMaterial(m_tiles[tileID]);
}

void_sex CWorld::changeTileset(CTileset& new_tileset) {
    m_tileset = &new_tileset;
}

CTileset& CWorld::getTileset() {
    return *m_tileset;
}