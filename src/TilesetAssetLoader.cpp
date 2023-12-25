#include <fstream>
#include <json.h>
#include <SDL_image.h>
#include "Tileset.h"
#include "Image.h"
#include "TilesetAssetLoader.h"

using nlohmann::json;

CTilesetAssetLoader::CTilesetAssetLoader(SDL_Renderer *renderer) : m_renderer(renderer)
{}

EAsset CTilesetAssetLoader::getType() const {
    return EAsset::Tileset;
}

bool CTilesetAssetLoader::doesPathMatch(const std::string& path) const {
    // TODO: Fix
    return true;
}

#include <iostream>
ACAsset* CTilesetAssetLoader::loadAsset(CAssetManager &assets, const std::string& path) {
    std::ifstream f(path);
    json data = json::parse(f);

    std::string tileset_file = std::string("environment/tilesets/").append(data["tileset_file"]);
    std::string tileset_name = data["tileset_name"];
    int tile_size = data["tile_size"];

    // std::cout << "tileset_file: " << tileset_file << std::endl;
    // std::cout << "tileset_name: " << tileset_name << std::endl;
    // std::cout << "tile_size: " << tile_size << std::endl;

	CImage *tileset_image = assets.fetchImage(tileset_file);
    CTileset *tileset = new CTileset(path, *tileset_image, tileset_name, tile_size);

    json jmats = data["materials"];
    if (jmats.type() == json::value_t::object) {
        std::map<std::string, std::string> mats = jmats;

        for (auto& elem : mats) {
            std::string key = elem.first;
            std::string value = elem.second;

            ETileMaterial material = ETileMaterial::None;
            int tile = std::stoi(key);

            if (value == "stone") {
                material = ETileMaterial::Stone;
            } else if (value == "panel") {
                material = ETileMaterial::Panel;
            } else if (value == "dirt") {
                material = ETileMaterial::Dirt;
            } else if (value == "wood") {
                material = ETileMaterial::Wood;
            }

            tileset->setMaterial(tile, material);
        }
    }

	return tileset;
}