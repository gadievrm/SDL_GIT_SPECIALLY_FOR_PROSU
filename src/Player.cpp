#include <cmath>
#include "Player.h"
#include "Main.h"

const int PLAYER_WIDTH = 20;
const int PLAYER_HEIGHT = 23;



const float moveSpeed = 0.004;
const float friction = 0.995;

bool Player::isDrawable() {
	return true;
}

bool Player::getFlipX(){
	return this->flipX;
}

void Player::logic(double dt)
{ 
	if (aKeyPressed) {
		this->flipX = true;
		this->velX -= moveSpeed * dt;
	}
	if (dKeyPressed) {
		this->flipX = false;
		this->velX += moveSpeed * dt;
	}
	if (wKeyPressed) {
		this->velY -= moveSpeed * dt; 
	}
	if(sKeyPressed) {
		this->velY += moveSpeed * dt;
	}

	this->setPosX(this->getPosX() + this->velX * dt);
	this->setPosY(this->getPosY() + this->velY * dt);

	this->velX *= pow(friction, dt);
	this->velY *= pow(friction, dt);
}

image_t *Player::getImage (){
	return this->image;
}

void Player::setImage(image_t *new_image) {
	this->image = new_image;
}

void Player::draw() {
	imageDraw(renderer, this->image, this->getPosX(), this->getPosY(), this->getFlipX());
}