#include "Player.h"
#include "Main.h"

const int PLAYER_WIDTH = 20;
const int PLAYER_HEIGHT = 23;

const float moveSpeed = 0.0008;
const float friction = 0.995;

bool Player::isDrawable() {
	return true;
}

bool Player::getFlipX(){
	return this->flipX;
}

void Player::logic()
{ 
	if (aKeyPressed) 
	{
		this->flipX = true;
		this->velX -= moveSpeed;
	}
	if (dKeyPressed){
		this->flipX = false;
		this->velX += moveSpeed;
	}
	if (wKeyPressed){
		this->velY -= moveSpeed; 
	}
	if(sKeyPressed){
		this->velY += moveSpeed;
	}

	this->setPosX(this->getPosX() + this->velX);
	this->setPosY(this->getPosY() + this->velY);

	this->velX *= friction;
	this->velY *= friction;
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