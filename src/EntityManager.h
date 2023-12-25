#pragma once
#include <vector>
#include <unordered_map>

class CEntityManager;
#include "Entity.h"

class CEntityManager {
private:
    std::vector<ACEntity*> m_entities;                              // ALL ENTITIES
    std::unordered_map<std::string, std::vector<ACEntity*>> m_tags; // For lookup
public:
    void addEntity(ACEntity &entity);
    bool removeEntity(ACEntity &entity);

    void addEntityWithName(const std::string &tag, ACEntity &entity);
    void removeEntitiesByName(const std::string &tag);
    std::vector<ACEntity*>& findEntitiesByName(const std::string &tag);

    const std::vector<ACEntity*>& getAllEntities();
};