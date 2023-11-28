#include <iostream>
#include "Graphics.h"
#include <SDL2/SDL_image.h>

image_t *imageLoad (const char *path, SDL_Renderer *renderer){
	SDL_Texture *texture;
	SDL_Surface *textureSurface = NULL;
	textureSurface = IMG_Load(path);

	if (textureSurface == NULL) {
		std::cout << IMG_GetError() << std::endl;
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(renderer, textureSurface);

	image_t *result = (image_t*) malloc(sizeof(image_t));
	result -> w = textureSurface->w;
	result -> h = textureSurface->h;
	result -> tex = texture;

	SDL_FreeSurface(textureSurface);

	return result;
}

void imageDraw (SDL_Renderer *rnd, image_t *target, int posX, int posY, bool flip){
	SDL_Rect dstRect {.x = posX, .y = posY, .w = target->w, .h = target->h};

	SDL_RenderCopyEx(rnd, target->tex, NULL, &dstRect, 0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
};