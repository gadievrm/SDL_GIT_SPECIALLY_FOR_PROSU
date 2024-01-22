#include "Map.h"
#include "World.h"
#include "Tileset.h"
#include <vector>
#include <fstream>
#include <json.h>
#include <filesystem>
namespace fs = std::filesystem;
using nlohmann::json;

#include "Player.h"
#include "Gem.h"


#include <iostream>
void MapLoad(TGameSystems systems, CAssetManager& assets, const fs::path& path, std::string& name, CEntityManager& entities) {
    json data = json::parse(std::ifstream(fs::path("data/maps") / path));
    json jworld;
    fs::path tileset_path;

    CTileset *tileset;

    name = data["name"];
    jworld = data["world"];

    tileset_path = fs::path("data/gfx/env/tilesets") / (std::string(jworld["tileset"]) + std::string(".json"));
    tileset = static_cast<CTileset*>(assets.fetchAsset(EAsset::Tileset, tileset_path));

    // World loading
    {
        json jsize = jworld["size"];
        std::vector<uint16_t> wtiles = jworld["tiles"];
        int ww = jsize[0];
        int wh = jsize[1];
        if (wtiles.size() != ww*wh) {
            std::cerr << "World size incorrect!" << std::endl;
            return;
        }
        fs::path bg_path = fs::path("env/bg") / (std::string(jworld["background"]));
        CImage *bg = assets.fetchImage(bg_path);
        CWorld* world = new CWorld(*tileset, *bg, ww, wh);
        world->putTiles(wtiles);
        entities.addWithName("0world", *world);
    }

    // Entity loading
    for (json jent : data["entities"]) {
        std::string class_name = jent["class"];

        ACEntity *ent = gEnts[class_name].load(jent);

        json jname = jent["name"];
        if (jname.type() == json::value_t::string) {
            entities.addWithName(jname, *ent);
        } else {
            entities.add(*ent);
        }
    }
}

void MapSave(TGameSystems systems, CAssetManager &assets, const std::filesystem::path& path, const std::string& name, CEntityManager& entities) {
    json jmap, jworld, jentities;
    
    CWorld *world = static_cast<CWorld*>(entities.findFirstByName("0world"));
    jworld["tileset"] = world->getTileset().getPath().value().stem();
    jworld["background"] = world->getBackgroundImage().getPath().value().filename();
    jworld["size"] = {world->getWidth(), world->getHeight()};
    jworld["tiles"] = world->getAllTiles();

    jentities = json::array();
    for (auto ent : entities.getAll()) {
        json jent;
        const std::string& class_name = ent->class_name;
        if (class_name == CWorld::CLASS_NAME) {
            continue;
        }

        jent = gEnts[class_name].save(ent);

        auto maybe_name = ent->getName();
        if (maybe_name.has_value()) {
            jent["name"] = maybe_name.value();
        }
        jent["class"] = class_name;
        jentities.push_back(jent);
    }

    jmap["world"] = jworld;
    jmap["entities"] = jentities;
    jmap["name"] = name;
    std::string data_to_write = jmap.dump(4);

    std::ofstream f(fs::path("data/maps") / path);
    f.write(data_to_write.c_str(), data_to_write.size());
}