#include <SDL2/SDL.h>
#include "Entity.h"

float ACEntity::getPosX() {
    return this->posX;
}

float ACEntity::getPosY() {
    return this->posY;
}

void ACEntity::setPosX(float new_posX) {
    this->posX = new_posX;
}

void ACEntity::setPosY(float new_posY) {
    this->posY = new_posY;
}

std::string ACEntity::getName() {
    return this->name;
}

void ACEntity::setName(std::string new_name) {
    this->name = new_name;
}