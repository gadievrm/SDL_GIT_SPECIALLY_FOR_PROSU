#pragma once
#include <vector>
#include "Entity.h"
#include "Image.h"
#include "Tileset.h"

class CWorld : public ACEntity {
private:
    CTileset &m_tileset;
    CImage &m_background;
    uint16_t m_width;
    uint16_t m_height;
    std::vector<uint16_t> m_tiles;
public:
    CWorld(CTileset &tileset, CImage& background, uint16_t width, uint16_t height);
    void putTiles(const std::vector<uint16_t>& tiles);
    void logic(double dt) override;
    void draw(CGraphics *graphics) override;
};