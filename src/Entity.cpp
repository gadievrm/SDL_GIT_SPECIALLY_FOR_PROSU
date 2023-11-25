#include <SDL2/SDL.h>
#include "Entity.h"

float Entity::getPosX() {
    return this->posX;
}

float Entity::getPosY() {
    return this->posY;
}

void Entity::setPosX(float new_posX) {
    this->posX = new_posX;
}

void Entity::setPosY(float new_posY) {
    this->posY = new_posY;
}

std::string Entity::getName() {
    return this->name;
}

void Entity::setName(std::string new_name) {
    this->name = new_name;
}