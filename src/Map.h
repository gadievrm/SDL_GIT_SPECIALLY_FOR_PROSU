#pragma once
#include <string>
#include "AssetManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "GameSystems.h"

void MapLoad(TGameSystems systems, CAssetManager &assets, const std::string& path, std::string& name, CEntityManager& entities);