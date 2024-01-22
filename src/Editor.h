#pragma once
#include <vector>
#include <string>
#include "Tileset.h"
#include "World.h"
#include "Camera.h"

class CEditor;
#include "Game.h"

class CEditor {
private:
    CGame& m_game;
    bool m_map_settings_open;
    bool m_tileset_settings_open;
    char m_map_name[128];
    char m_map_background_path[256];
    char m_map_tileset_path[256];
    int  m_map_size[2];
    int  m_selected_tile;
    int  m_selected_entity;
    ETileMaterial m_mat_active;
    std::vector<std::string> m_editor_entity_list;
public:
    CEditor(CGame& game);
    void begin();
    void update(double dt);
};