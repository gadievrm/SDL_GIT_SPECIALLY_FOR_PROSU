#include <SDL.h>
#include "Entity.h"

ACEntity::ACEntity(const std::string& class_name) : m_class_name(class_name), m_name(std::nullopt), m_posX(0.0f), m_posY(0.0f)
{}

float ACEntity::getPosX() {
    return m_posX;
}

float ACEntity::getPosY() {
    return m_posY;
}

void ACEntity::setPosX(float new_posX) {
    m_posX = new_posX;
}

void ACEntity::setPosY(float new_posY) {
    m_posY = new_posY;
}

std::optional<std::string> ACEntity::getName() {
    return m_name;
}

void ACEntity::setName(const std::string& new_name) {
    m_name = new_name;
}

const std::string& ACEntity::getClassName() {
    return m_class_name;
}