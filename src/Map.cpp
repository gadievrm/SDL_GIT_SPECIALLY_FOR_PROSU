#include "Map.h"
#include "World.h"
#include "Tileset.h"
#include <vector>
#include <fstream>
#include <json.h>
using nlohmann::json;

#include "Player.h"
#include "Gem.h"


#include <iostream>
void MapLoad(TGameSystems systems, CAssetManager& assets, const std::string& path, std::string& name, CEntityManager& entities) {
    json data = json::parse(std::ifstream(path));
    json jworld;
    std::string tileset_path;

    CTileset *tileset;

    name = data["name"];
    jworld = data["world"];

    tileset_path = std::string("data/gfx/environment/tilesets/").append(jworld["tileset"]).append(".json");
    tileset = static_cast<CTileset*>(assets.fetchAsset(EAsset::Tileset, tileset_path));

    // World loading
    {
        json jsize = jworld["size"];
        std::vector<uint16_t> wtiles = jworld["tiles"];
        int wh = jsize[0];
        int ww = jsize[1];
        if (wtiles.size() != wh*ww) {
            std::cerr << "World size incorrect!" << std::endl;
            return;
        }
        std::string bg_path = std::string("environment/bg/").append(jworld["background"]);
        CImage *bg = assets.fetchImage(bg_path);
        CWorld* world = new CWorld(*tileset, *bg, ww, wh);
        world->putTiles(wtiles);
        entities.addEntityWithName("0world", *world);
    }

    // Entity loading
    for (json jent : data["entities"]) {
        std::string class_name = jent["class"];
        ACEntity *ent;

        if (class_name == "player") {
            json jpos = jent["pos"];
            CPlayer *player = new CPlayer(systems);
            player->setPosX(jpos[0]);
            player->setPosY(jpos[1]);

            ent = player;
        } else if (class_name == "item_gem") {
            json jpos = jent["pos"];
            CGem *gem = new CGem(systems);
            gem->setPosX(jpos[0]);
            gem->setPosY(jpos[1]);

            ent = gem;
        } else {
            std::cerr << "UNKNOWN CLASS NAME! (" << class_name << ")" << std::endl;
            continue;
        }

        json jname = jent["name"];
        if (jname.type() == json::value_t::string) {
            entities.addEntityWithName(jname, *ent);
        } else {
            entities.addEntity(*ent);
        }
    }
}