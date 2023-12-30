#include "EntityManager.h"

void CEntityManager::addWithName(const std::string& tag, ACEntity& entity) {
    entity.setName(tag);
    m_entities.push_back(&entity);
    m_tags[tag].push_back(&entity);
}

void CEntityManager::add(ACEntity &entity) {
    m_entities.push_back(&entity);
}

bool CEntityManager::remove(ACEntity &entity) {
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

void CEntityManager::removeAll() {
    m_tags.clear();

    for (auto &ent : m_entities) {
        delete ent;
    }
    m_entities.clear();
}

void CEntityManager::removeByName(const std::string& tag) {
    m_tags.erase(tag);

    for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
        if ((*it)->getName() != tag) continue;
        m_entities.erase(it);
        delete *it;
    }
}

std::vector<ACEntity*>& CEntityManager::findByName(const std::string &tag) {
    return m_tags[tag];
}

ACEntity* CEntityManager::findFirstByName(const std::string& tag) {
    return m_tags[tag][0];
}

const std::vector<ACEntity*>& CEntityManager::getAll() {
    return m_entities;
}