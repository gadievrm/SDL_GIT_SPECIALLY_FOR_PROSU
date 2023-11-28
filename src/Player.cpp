#include <cmath>
#include "Player.h"

const int PLAYER_WIDTH = 20;
const int PLAYER_HEIGHT = 23;

const float moveSpeed = 0.004;
const float friction = 0.995;

Player::Player(Game *game) {
	this->game = game;
}

bool Player::isDrawable() {
	return true;
}

bool Player::getFlipX(){
	return this->flipX;
}

void Player::logic(double dt)
{ 
	if (getGame()->getAKeyPressed()) {
		this->flipX = true;
		this->velX -= moveSpeed * dt;
	}
	if (getGame()->getDKeyPressed()) {
		this->flipX = false;
		this->velX += moveSpeed * dt;
	}
	if (getGame()->getWKeyPressed()) {
		this->velY -= moveSpeed * dt; 
	}
	if (getGame()->getSKeyPressed()) {
		this->velY += moveSpeed * dt;
	}

	this->setPosX(this->getPosX() + this->velX * dt);
	this->setPosY(this->getPosY() + this->velY * dt);

	this->velX *= pow(friction, dt);
	this->velY *= pow(friction, dt);
}

Game *Player::getGame() {
	return game;
}

void Player::setGame(Game *newgame) {
	game = newgame;
}

image_t *Player::getImage (){
	return this->image;
}

void Player::setImage(image_t *new_image) {
	this->image = new_image;
}

void Player::draw() {
	imageDraw(getGame()->getRenderer(), this->image, this->getPosX(), this->getPosY(), this->getFlipX());
}