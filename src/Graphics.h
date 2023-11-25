#pragma once

#include <SDL2/SDL.h>

struct image_t{
	int w; int h;
	SDL_Texture *tex;
};

image_t *imageLoad (const char *path, SDL_Renderer *renderer);
void imageDraw (SDL_Renderer *rnd, image_t *target, int posX, int posY, bool flip = false);
