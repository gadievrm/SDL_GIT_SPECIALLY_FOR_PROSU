#pragma once
#include <optional>
#include <string>
#include <unordered_map>
#include <tuple>
#include "Entity.h"

typedef ACEntity*                                    FEntityLoader(std::optional<std::unordered_map<std::string, std::string>> options);
typedef std::unordered_map<std::string, std::string> FEntitySaver (ACEntity*                                                   entity);

struct TEntityEntry {
    FEntityLoader *load;
    FEntitySaver *save;
};


extern std::unordered_map<std::string, TEntityEntry> gEnts;