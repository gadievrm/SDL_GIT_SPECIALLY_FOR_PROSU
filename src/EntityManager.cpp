#include "EntityManager.h"

void CEntityManager::addEntityWithName(const std::string &tag, ACEntity &entity) {
    m_entities.push_back(&entity);
    m_tags[tag].push_back(&entity);
}

void CEntityManager::addEntity(ACEntity &entity) {
    m_entities.push_back(&entity);
}

bool CEntityManager::removeEntity(ACEntity &entity) {
    bool removed = false;
    // Remove from m_entities
    for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
        if (&entity != *it) continue;

        m_entities.erase(it);
        removed = true;
        break;
    }

    // Remove from m_tags
    for (auto outer_it = m_tags.begin(); outer_it != m_tags.end(); outer_it++) {
        auto vec = outer_it->second;
        for (auto it = vec.begin(); it != vec.end(); it++) {
            if (&entity != *it) continue;

            vec.erase(it);
            removed = true;
        }
    }

    return removed;
}

void CEntityManager::removeEntitiesByName(const std::string &tag) {
    m_tags.erase(tag);
}

std::vector<ACEntity*>& CEntityManager::findEntitiesByName(const std::string &tag) {
    return m_tags[tag];
}

const std::vector<ACEntity*>& CEntityManager::getAllEntities() {
    return m_entities;
}