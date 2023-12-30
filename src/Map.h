#pragma once
#include <filesystem>
#include <string>
#include "AssetManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "GameSystems.h"

void MapLoad(TGameSystems systems, CAssetManager &assets, const std::filesystem::path& path, std::string& name, CEntityManager& entities);
void MapSave(TGameSystems systems, CAssetManager &assets, const std::filesystem::path& path, const std::string& name, CEntityManager& entities);