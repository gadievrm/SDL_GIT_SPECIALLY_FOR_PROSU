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
    void add(ACEntity &entity);
    bool remove(ACEntity &entity);
    void removeAll();

    void addWithName(const std::string &tag, ACEntity &entity);
    void removeByName(const std::string &tag);
    std::vector<ACEntity*>& findByName(const std::string &tag);
    ACEntity* findFirstByName(const std::string& tag);

    const std::vector<ACEntity*>& getAll();
};