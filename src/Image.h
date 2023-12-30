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
    CImage(std::optional<std::filesystem::path> path, SDL_Texture *texture, int width, int height);
};

struct image_islice_t {
    const CImage &image;
    int x;
    int y;
    int w;
    int h;
};

struct image_fslice_t {
    const CImage &image;
    float x;
    float y;
    float w;
    float h;
};