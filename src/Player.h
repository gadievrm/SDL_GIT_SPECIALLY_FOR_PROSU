#pragma once

#include "Game.h"
#include "Entity.h"
#include "Graphics.h"

class Game;
class Player : public Entity {
    private:
        float velX;
        float velY;
        bool flipX;
        image_t *image;
        Game *game;

    public:
        Player(Game *game);

        bool getFlipX();
        image_t *getImage();
        void setImage(image_t *new_image);
        Game *getGame();
        void setGame(Game *newgame);

        virtual bool isDrawable();
        virtual void logic(double dt);
        virtual void draw(Graphics *graphics);

};