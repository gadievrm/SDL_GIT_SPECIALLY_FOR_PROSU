#pragma once
#include <SDL2/SDL.h>
#include "Asset.h"

class CImage : public ACAsset {
private:
	int m_width; 
    int m_height;
	SDL_Texture *m_texture;
public:
    int getWidth();
    int getHeight();
    SDL_Texture*& getTexture();
    CImage(std::optional<std::string> path, SDL_Texture *texture, int width, int height);
};