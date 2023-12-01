#pragma once

#include "Game.h"
#include "Entity.h"
#include "Graphics.h"
#include "Input.h"
#include "GameSystems.h"

class Game;
class Player : public Entity {
private:
    Graphics *graphics;
    Input *input;

    image_t *image;

    float velX;
    float velY;
    bool flipX;

public:
    Player(GameSystems systems);

    bool getFlipX();
    image_t *getImage();
    void setImage(image_t *new_image);

    virtual bool isDrawable();
    virtual void logic(double dt);
    virtual void draw(Graphics *graphics);
};