#include <imgui.h>
#include <filesystem>
#include <ranges>
#include <algorithm>
#include <fstream>
#include <json.h>
#include "Editor.h"
#include "GameSetup.h"
#include "EntityEntries.h"
#include "Map.h"

namespace fs = std::filesystem;
using nlohmann::json;

CEditor::CEditor(CGame& game) : m_game(game) {};

void CEditor::begin() {
    m_map_settings_open = false;
    m_tileset_settings_open = false;
    m_selected_tile = 0;
    m_selected_entity = 0;
}

void CEditor::update(double dt) {
    // -----------------------------------------------------
    // -----------------------------------------------------
    //                    USER INTERFACE
    // -----------------------------------------------------
    // -----------------------------------------------------
    #define TAB_TILES 0
    #define TAB_ENTITIES 1
    
    auto& tileset  = m_game.m_tileset;
    auto& world    = m_game.m_world;
    auto& input    = m_game.m_input;
    auto& graphics = m_game.m_graphics;
    auto& entities = m_game.m_entities;
    auto& camera   = m_game.m_camera;
    auto& systems  = m_game.m_systems;
    auto& assets   = m_game.m_assets;

    int editor_tab;
    int tile_size = tileset->getTileSize();

    if (m_map_settings_open) {
        if (ImGui::Begin("Map settings", &m_map_settings_open)) {

            ImGui::BeginTable("TMapSettings", 2);
                ImGui::TableNextColumn();
                ImGui::Text("Name");
                ImGui::TableNextColumn();
                ImGui::InputText("##Name", m_map_name, 127);
                ImGui::TableNextRow();

                ImGui::TableNextColumn();
                ImGui::Text("Size");
                ImGui::TableNextColumn();
                ImGui::InputInt2("##Size", m_map_size, 0);
                ImGui::TableNextRow();

                ImGui::TableNextColumn();
                ImGui::Text("Background");
                ImGui::TableNextColumn();
                ImGui::InputText("##Bg", m_map_background_path, 255);
                ImGui::TableNextRow();

                ImGui::TableNextColumn();
                ImGui::Text("Tileset");
                ImGui::TableNextColumn();
                ImGui::InputText("##Tileset", m_map_tileset_path, 255);
                ImGui::TableNextRow();
            ImGui::EndTable();

            if (ImGui::Button("OK")) {
                fs::path bg_path(m_map_background_path);
                fs::path tileset_path(m_map_tileset_path);
                int& new_width = m_map_size[0];
                int& new_height = m_map_size[1];

                // If everything went well

                m_game.m_map_name = m_map_name;
                world->resize(new_width, new_height, true);
                m_map_settings_open = false;
                // MapSave(systems, assets, map_path, map_name, m_entities);
            }
        }
        ImGui::End();
    }

    if (m_tileset_settings_open) {
        ImGui::SetNextWindowSizeConstraints(ImVec2(4 * (tile_size + 15) + 10, 400), ImVec2(1000, 1000));
        if (ImGui::Begin("Tileset", &m_tileset_settings_open)) {
            for (int i = 0; i < int(ETileMaterial::COUNT); i++) {
                ETileMaterial mat = ETileMaterial(i);
                if (ImGui::RadioButton(TileMaterialToString(mat), m_mat_active == mat))
                    m_mat_active = mat;
            }

            ImGui::BeginChild("TileSetScroll");
                ImGui::BeginTable("TileSet", 4, 0);
                for (int i = 0; i < tileset->getSize(); i++) {
                    image_fslice_t tile = tileset->getTileImageSliceNormalized(i);

                    if (i % 4 == 0) ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::Text("%s", TileMaterialToString(tileset->getMaterial(i).value()));

                    bool chosen =
                    ImGui::ImageButton(
                        (std::string("tiles_") + (std::to_string(i))).c_str(),
                        tile.image.getTexture(),
                        ImVec2(tile_size, tile_size),
                        ImVec2(tile.x, tile.y),
                        ImVec2(tile.x + tile.w, tile.y + tile.h),
                        ImVec4(0, 0, 0, 0),
                        ImVec4(1, 1, 1, 1)
                    );

                    if (chosen) {
                        tileset->setMaterial(i, m_mat_active);
                    }
                }
                ImGui::EndTable();
            ImGui::EndChild();
            if (ImGui::Button("Save")) {
                std::ofstream f(tileset->getPath().value());

                json jmaterials;
                auto& tileset_materials = tileset->getAllMaterials();
                for (int i = 0; i < tileset_materials.size(); i++) {
                    jmaterials[std::to_string(i)] = TileMaterialToString(tileset_materials[i]);
                }

                json jtileset;
                jtileset["tileset_name"] = tileset->getName();
                jtileset["tileset_file"] = tileset->getTileImageSlice(0).image.getPath()->filename();
                jtileset["tile_size"] = tile_size;
                jtileset["materials"] = jmaterials;

                std::string data_to_write = jtileset.dump(4);
                f.write(data_to_write.c_str(), data_to_write.size());
            }
        }
        ImGui::End();
    }

    ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::SetWindowSize(ImVec2(tile_size * 10, SCREEN_HEIGHT), ImGuiCond_Once);

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New")) {
                    // Free current map
                    entities.removeAll();

                    // Make default map
                    m_game.m_map_path = "editor_temp.json";
                    world = new CWorld(CWorld::makeDefault(assets));
                    entities.addWithName("0world", *(world));
                }
                if (ImGui::MenuItem("Open")) {
                    
                }
                if (ImGui::MenuItem("Save")) {
                    MapSave(systems, assets, m_game.m_map_path, m_game.m_map_name, entities);
                }
                if (ImGui::MenuItem("Save As...")) {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Settings")) {
                if (ImGui::MenuItem("Map settings")) {
                    m_map_settings_open ^= 1;

                    // Initialize map settings menu
                    if (m_map_settings_open) {
                        strcpy(m_map_name, m_game.m_map_name.c_str());
                        m_map_size[0] = world->getWidth();
                        m_map_size[1] = world->getHeight();

                        strcpy(m_map_background_path, world->getBackgroundImage().getPath().value().filename().string().c_str());
                        strcpy(m_map_tileset_path, world->getTileset().getPath().value().stem().string().c_str());
                    }
                }
                if (ImGui::MenuItem("Tileset settings")) {
                    m_tileset_settings_open ^= 1;

                    if (m_tileset_settings_open) {
                        m_mat_active = ETileMaterial::None;
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::BeginTabBar("EditorTabs");
            if (ImGui::BeginTabItem("Tiles")) {
                editor_tab = TAB_TILES;
                ImGui::BeginChild("EditorMenuTiles");
                ImGui::BeginTable("TEditorMenuTiles", 4, 0, ImVec2(0.0, 0.0), 0.0);
                for (int i = 0; i < tileset->getSize(); i++) {
                    image_fslice_t tile = tileset->getTileImageSliceNormalized(i);
                    bool selected = m_selected_tile == i;

                    if (i % 4 == 0) ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    bool chosen = 
                    ImGui::ImageButton(
                        (std::string("tile_") + (std::to_string(i))).c_str(),
                        tile.image.getTexture(),
                        ImVec2(tile_size, tile_size),
                        ImVec2(tile.x, tile.y),
                        ImVec2(tile.x + tile.w, tile.y + tile.h),
                        ImVec4(0, 0, 0, 0),
                        ImVec4(1, 1, selected ? 0.2 : 1, 1.0)
                    );

                    if (chosen) m_selected_tile = i;
                }
                ImGui::EndTable();
                ImGui::EndChild();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Entities")) {
                if (editor_tab != TAB_ENTITIES) {
                    auto kv = std::views::keys(gEnts);
                    m_editor_entity_list = std::vector(kv.begin(), kv.end());
                    std::sort(m_editor_entity_list.begin(), m_editor_entity_list.end());
                }
                editor_tab = TAB_ENTITIES;
                ImGui::BeginChild("EntityList");
                    int i = 0;
                    for (auto& entity_class : m_editor_entity_list) {
                        if (ImGui::Selectable(entity_class.c_str(), i == m_selected_entity))
                            m_selected_entity = i;
                        i++;
                    }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
        ImGui::EndTabBar();
    ImGui::End();

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                        LOGIC
    // -----------------------------------------------------
    // -----------------------------------------------------
    float cameraX, cameraY;
    camera.getPos(cameraX, cameraY);
    int selected_tile_x, selected_tile_y;
    switch (editor_tab) {
        case TAB_TILES:
            selected_tile_x = cameraX + input.getMouseX();
            selected_tile_y = cameraY + input.getMouseY();
            world->convertToTileCoords(selected_tile_x, selected_tile_y);
            if (input.getHeld(EKey::MouseLeft)) {
                world->setTile(selected_tile_x, selected_tile_y, m_selected_tile);
            }
            if (input.getPressed(EKey::MouseMiddle)) {
                std::optional<int> maybe_tile = world->getTile(selected_tile_x, selected_tile_y);
                if (maybe_tile.has_value()) 
                    m_selected_tile = maybe_tile.value();
            }
            break;
        case TAB_ENTITIES:
            break;
    }

    camera.editor_update(systems);
    camera.update(dt);

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                       OUTPUT
    // -----------------------------------------------------
    // -----------------------------------------------------
    graphics->setOffset(-cameraX, -cameraY);
    for (auto entity : entities.getAll()) {
        entity->draw(graphics);
        if (editor_tab == TAB_TILES && (entity == world)) {
            world->drawTileInWorld(graphics, m_selected_tile, selected_tile_x, selected_tile_y);
        }
    }

    #undef TAB_TILES
    #undef TAB_ENTITIES
}