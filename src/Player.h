#pragma once

#include "Entity.h"
#include "Graphics.h"

class Player : public  Entity {
    private:
        float velX;
        float velY;
        bool flipX;
        image_t *image;

    public:
        bool getFlipX();
        image_t *getImage();
        void setImage(image_t *new_image);

        virtual bool isDrawable();
        virtual void logic();
        virtual void draw();

};