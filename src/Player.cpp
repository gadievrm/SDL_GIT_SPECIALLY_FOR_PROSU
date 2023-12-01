#include <cmath>
#include <iostream>
#include "Player.h"

const int PLAYER_WIDTH = 20;
const int PLAYER_HEIGHT = 23;

const float moveSpeed = 0.004;
const float friction = 0.995;

Player::Player(GameSystems systems) {
    this->graphics = systems.graphics;
    this->input = systems.input;

    // Важно ставить значения по-умолчанию
    // Иначе в значениях пермененных - мусор
    velX = velY = 0.0;
    flipX = false;
    image = NULL;
}

bool Player::isDrawable() {
    return true;
}

bool Player::getFlipX() {
    return this->flipX;
}

void Player::logic(double dt) {
    if (input->getAKeyPressed()) {
        this->flipX = true;
        this->velX -= moveSpeed * dt;
    }
    if (input->getDKeyPressed()) {
        this->flipX = false;
        this->velX += moveSpeed * dt;
    }
    if (input->getWKeyPressed()) {
        this->velY -= moveSpeed * dt;
    }
    if (input->getSKeyPressed()) {
        this->velY += moveSpeed * dt;
    }

    this->setPosX(this->getPosX() + this->velX * dt);
    this->setPosY(this->getPosY() + this->velY * dt);

    this->velX *= pow(friction, dt);
    this->velY *= pow(friction, dt);
}

image_t *Player::getImage() {
    return this->image;
}

void Player::setImage(image_t *new_image) {
    this->image = new_image;
}

void Player::draw(Graphics *graphics) {
    graphics->drawImage(this->image, this->getPosX(), this->getPosY(), this->getFlipX());
}
