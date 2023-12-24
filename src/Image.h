#pragma once
#include <SDL.h>
#include "Asset.h"

class CImage : public ACAsset {
private:
	int m_width; 
    int m_height;
	SDL_Texture *m_texture;
public:
    int getWidth() const;
    int getHeight() const;
    SDL_Texture*& getTexture() const;
    CImage(std::optional<std::string> path, SDL_Texture *texture, int width, int height);
};

struct image_slice_t {
    const CImage &image;
    int x;
    int y;
    int w;
    int h;
};