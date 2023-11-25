#pragma once

#include <string>
#include <SDL2/SDL.h>

class Entity {
private:
    std::string name;
    float posX;
    float posY;

    
public:
    float getPosX();
    float getPosY();
    void setPosX(float new_posX);
    void setPosY(float new_posY);
    virtual bool isDrawable() = 0;
    virtual void logic() = 0;
    virtual void draw() = 0;


    std::string getName();
    void setName(std::string new_name);
};