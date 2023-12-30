#include <iostream>
#include <fstream>
#include "GameSetup.h"
#include "Game.h"
#include "Gem.h"

#include "ImageAssetLoader.h"
#include "SoundAssetLoader.h"
#include "TilesetAssetLoader.h"
#include "Tileset.h"

#include "Map.h"

#include "DebugUI.h"

#include "Console.h"

#include <json.h>

namespace fs = std::filesystem;
using nlohmann::json;

CGame::CGame() : m_inited(false) {}

CGame* CGame::init() {
    CGame* game = new CGame();

    game->m_window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (game->m_window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
        delete game;
        return nullptr;
    }

    game->m_graphics = CGraphics::init(game->m_window);
    SDL_Renderer *renderer = game->m_graphics->getRenderer();

    game->m_systems = {
        .input          = &game->m_input    ,
        .graphics       =  game->m_graphics ,
        .audio          =  CAudio::init()   ,
        .entities       = &game->m_entities ,
        .assets         = &game->m_assets
    };

    game->m_assets.addLoader(*new CImageAssetLoader(renderer));
    game->m_assets.addLoader(*new CSoundAssetLoader());
    game->m_assets.addLoader(*new CTilesetAssetLoader(renderer));

    game->m_debug_ui = CDebugUI::init(game->m_window, renderer);

    game->m_inited = true;

    return game;
}

CGame::~CGame() {
    if (!m_inited) return;

    delete m_graphics;
    SDL_DestroyWindow(m_window);
}

void CGame::start() {
    if (!m_inited) {
        return;
    }

    m_quit = false;
    m_ticks = SDL_GetTicks64();
    m_frames_counted = 0;
    m_frametime_last = SDL_GetPerformanceCounter();
    m_performance_frequency = SDL_GetPerformanceFrequency();

    // startGaming();
    startMapEditor();
}

void CGame::loadMap(const std::filesystem::path& map_path) {
    MapLoad(m_systems, m_assets, map_path, m_map_name, m_entities);
    m_map_path = map_path;
}

void CGame::startMainMenu() {

}

void CGame::startGaming() {
    m_state = EGameState::Gaming;
    loadMap("out.json");
    m_main_player = static_cast<CPlayer*>(m_entities.findFirstByName("player0"));
    m_camera.followEntity(m_main_player, true);

    for (auto entity : m_entities.getAll()) {
        entity->init(m_systems);
    }
}

void CGame::startMapEditor() {
    m_state = EGameState::MapEditor;
    loadMap("out.json");
    m_world = static_cast<CWorld*>(m_entities.findFirstByName("0world"));
    m_tileset = &m_world->getTileset();
}

void CGame::doMainMenu(double delta_time) {
    m_state = EGameState::MainMenu;
}

void CGame::doGaming(double delta_time) {
    // -----------------------------------------------------
    // -----------------------------------------------------
    //                      LOGIC
    // -----------------------------------------------------
    // -----------------------------------------------------
    for (auto entity : m_entities.getAll()) {
        entity->logic(delta_time);
    }
    m_camera.update(delta_time);

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                       OUTPUT
    // -----------------------------------------------------
    // -----------------------------------------------------
    float cameraX, cameraY;
    m_camera.getPos(cameraX, cameraY);
    m_graphics->setOffset(-cameraX, -cameraY);
    for (auto entity : m_entities.getAll()) {
        entity->draw(m_graphics);
    }
}

void CGame::doMapEditor(double delta_time) {
    // -----------------------------------------------------
    // -----------------------------------------------------
    //                    USER INTERFACE
    // -----------------------------------------------------
    // -----------------------------------------------------
    static bool map_settings_open = false;
    static bool tileset_settings_open = false;
    static char map_name[128] = {0};
    static char map_background_path[256] = {0};
    static char map_tileset_path[256] = {0};
    static int map_size[2];
    static ETileMaterial mat_active;

    int tile_size = m_tileset->getTileSize();

    if (map_settings_open) {
        if (ImGui::Begin("Map settings", &map_settings_open)) {
            ImGui::InputText("Map name", map_name, 127);
            ImGui::InputInt2("Map size", map_size, 0);
            ImGui::InputText("Background image", map_background_path, 255);
            ImGui::InputText("Tileset", map_tileset_path, 255);

            if (ImGui::Button("OK")) {
                // MapSave(m_systems, m_assets, map_path, map_name, m_entities);
                fs::path bg_path(map_background_path);
                fs::path tileset_path(map_tileset_path);
                int& new_width = map_size[0];
                int& new_height = map_size[1];

                // If everything went well

                m_map_name = map_name;
                m_world->resize(new_width, new_height, true);
                map_settings_open = false;
            }
        }
        ImGui::End();
    }

    if (tileset_settings_open) {
        ImGui::SetNextWindowSizeConstraints(ImVec2(4 * (tile_size + 15) + 10, 400), ImVec2(1000, 1000));
        if (ImGui::Begin("Tileset", &tileset_settings_open)) {
            for (int i = 0; i < int(ETileMaterial::COUNT); i++) {
                ETileMaterial mat = ETileMaterial(i);
                if (ImGui::RadioButton(TileMaterialToString(mat),  mat_active == mat))
                    mat_active = mat;
            }

            ImGui::BeginChild("TileSetScroll");
                ImGui::BeginTable("TileSet", 4, 0, ImVec2(0.0, 0.0), 0.0);
                for (int i = 0; i < m_tileset->getSize(); i++) {
                    image_fslice_t tile = m_tileset->getTileImageSliceNormalized(i);

                    if (i % 4 == 0) ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::Text("%s", TileMaterialToString(m_tileset->getMaterial(i).value()));

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
                        m_tileset->setMaterial(i, mat_active);
                    }
                }
                ImGui::EndTable();
            ImGui::EndChild();
            if (ImGui::Button("Save")) {
                std::ofstream f(m_tileset->getPath().value());

                json jmaterials;
                auto& tileset_materials = m_tileset->getAllMaterials();
                for (int i = 0; i < tileset_materials.size(); i++) {
                    jmaterials[std::to_string(i)] = TileMaterialToString(tileset_materials[i]);
                }

                json jtileset;
                jtileset["tileset_name"] = m_tileset->getName();
                jtileset["tileset_file"] = m_tileset->getTileImageSlice(0).image.getPath()->filename();
                jtileset["tile_size"] = tile_size;
                jtileset["materials"] = jmaterials;

                std::string data_to_write = jtileset.dump(4);
                f.write(data_to_write.c_str(), data_to_write.size());
            }
        }
        ImGui::End();
    }

    ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar);
        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::SetWindowSize(ImVec2(0, SCREEN_HEIGHT), ImGuiCond_Once);

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New")) {
                    // Free current map
                    m_entities.removeAll();

                    // Make default map
                    m_map_path = "editor_temp.json";
                    m_world = new CWorld(CWorld::makeDefault(m_assets));
                    m_entities.addWithName("0world", *m_world);
                }
                if (ImGui::MenuItem("Open")) {
                    
                }
                if (ImGui::MenuItem("Save")) {
                    MapSave(m_systems, m_assets, m_map_path, m_map_name, m_entities);
                }
                if (ImGui::MenuItem("Save As...")) {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Settings")) {
                if (ImGui::MenuItem("Map settings")) {
                    map_settings_open ^= 1;

                    // Initialize map settings menu
                    if (map_settings_open) {
                        strcpy(map_name, m_map_name.c_str());
                        map_size[0] = m_world->getWidth();
                        map_size[1] = m_world->getHeight();
                    }
                }
                if (ImGui::MenuItem("Tileset settings")) {
                    tileset_settings_open ^= 1;

                    if (tileset_settings_open) {
                        mat_active = ETileMaterial::None;
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        static int selected_tile = 0;
        ImGui::BeginTable("EditorMenuTiles", 4, 0, ImVec2(0.0, 0.0), 0.0);
        for (int i = 0; i < m_tileset->getSize(); i++) {
            image_fslice_t tile = m_tileset->getTileImageSliceNormalized(i);
            bool selected = selected_tile == i;

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

            if (chosen) selected_tile = i;
        }
        ImGui::EndTable();
    ImGui::End();

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                        LOGIC
    // -----------------------------------------------------
    // -----------------------------------------------------
    float cameraX, cameraY;
    m_camera.getPos(cameraX, cameraY);
    int selected_tile_x = cameraX + m_input.getMouseX();
    int selected_tile_y = cameraY + m_input.getMouseY();
    m_world->convertToTileCoords(selected_tile_x, selected_tile_y);
    if (m_input.getHeld(EKey::MouseLeft)) {
        m_world->setTile(selected_tile_x, selected_tile_y, selected_tile);
    }
    if (m_input.getPressed(EKey::MouseMiddle)) {
        std::optional<int> maybe_tile = m_world->getTile(selected_tile_x, selected_tile_y);
        if (maybe_tile.has_value()) 
            selected_tile = maybe_tile.value();
    }

    m_camera.editor_update(m_systems);
    m_camera.update(delta_time);

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                       OUTPUT
    // -----------------------------------------------------
    // -----------------------------------------------------
    m_graphics->setOffset(-cameraX, -cameraY);
    for (auto entity : m_entities.getAll()) {
        entity->draw(m_graphics);
        if (entity == m_world) {
            m_world->drawTileInWorld(m_graphics, selected_tile, selected_tile_x, selected_tile_y);
        }
    }
}

bool CGame::run() {
    if (m_quit || !m_inited) {
        return false;
    }

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                  TIME & PERFORMANCE
    // -----------------------------------------------------
    // -----------------------------------------------------
    double frametime_now = SDL_GetPerformanceCounter();
    double delta_time = (frametime_now - m_frametime_last) * 1000.0 / m_performance_frequency;
    m_frametime_last = frametime_now;
    if (SDL_GetTicks64() - m_ticks > 1000) {
        m_frames_counted = 0;
        m_ticks = SDL_GetTicks64();
    }
    m_frames_counted++;

    m_debug_ui->beginFrame();
    // ImGui::ShowDemoWindow();

    // -----------------------------------------------------
    // -----------------------------------------------------
    //                        INPUT
    // -----------------------------------------------------
    // -----------------------------------------------------
    m_input.update();
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        m_debug_ui->handleEvent(e);
        
        if (!m_debug_ui->isTakingKeyboard() && e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            m_input.processKeyEvent(e);
        }

        if (!m_debug_ui->isTakingMouse()) {
            float scaleX;
            float scaleY;
            m_graphics->getScaling(scaleX, scaleY);
            m_input.processMouseEvent(e, 1 / scaleX, 1 / scaleY);
        }

        if ((e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) || e.type == SDL_QUIT) {
            m_quit = true;
        }
    }

    gConsole.update(m_systems);
    switch (m_state) {
        case EGameState::MainMenu:
            doMainMenu(delta_time);
            break;
        case EGameState::MapEditor:
            doMapEditor(delta_time);
            break;
        case EGameState::Gaming:
            doGaming(delta_time);
            break;
    }
    gConsole.draw();

    m_graphics->removeScaling();
    m_debug_ui->endFrame();
    m_graphics->addScaling();

    m_graphics->present();

    return !m_quit;
}