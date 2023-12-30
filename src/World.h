#pragma once
#include <vector>
#include "Entity.h"
#include "Image.h"
#include "Tileset.h"
#include <optional>

#define void_sex void

class CWorld : public ACEntity {
private:
    CTileset* m_tileset;
    CImage& m_background;
    uint16_t m_width;
    uint16_t m_height;
    std::vector<uint16_t> m_tiles;
public:
    static inline const std::string CLASS_NAME = "world";

    CWorld(CTileset& tileset, CImage& background, uint16_t width, uint16_t height);
    static CWorld makeDefault(CAssetManager &assets);
    uint16_t getWidth();
    uint16_t getHeight();
    void_sex resize(uint16_t new_width, uint16_t new_height, bool copy_tiles);
    void_sex changeBackgroundImage(CImage& new_image);
    CImage& getBackgroundImage();
    void_sex putTiles(const std::vector<uint16_t>& tiles);
    void_sex init(TGameSystems systems) override;
    void_sex logic(double dt) override;
    void_sex draw(CGraphics *graphics) override;
    void_sex convertToTileCoords(int &x, int &y);
    void_sex drawTileInWorld(CGraphics *graphics, int tile, int x, int y);
    void_sex setTile(int x, int y, int tile);
    std::optional<int> getTile(int x, int y);
    std::vector<uint16_t>& getAllTiles();
    int getTileSize();
    std::optional<ETileMaterial> getTileMaterialAt(float x, float y);
    void_sex changeTileset(CTileset& new_tileset);
    CTileset& getTileset();
};