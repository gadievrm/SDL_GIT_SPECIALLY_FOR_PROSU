#include <iostream>
#include "Graphics.h"
#include <SDL2/SDL_image.h>

Graphics* Graphics::init(SDL_Window *window) {

	Graphics *graphics = new Graphics();
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetVSync(renderer, 1);

	graphics->renderer = renderer;

	return graphics;
}

Graphics::~Graphics() {
	SDL_DestroyRenderer(renderer);
}

image_t *Graphics::loadImage(const char *path) {
	SDL_Texture *texture;
	SDL_Surface *textureSurface = NULL;
	textureSurface = IMG_Load(path);

	if (textureSurface == NULL) {
		std::cerr << IMG_GetError() << std::endl;
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

void Graphics::drawImageFullscreen(image_t *target) {
	SDL_RenderCopy(renderer, target->tex, NULL, NULL);
}

void Graphics::drawImage(image_t *target, int posX, int posY, bool flip) {
	SDL_Rect dstRect {.x = posX, .y = posY, .w = target->w, .h = target->h};

	SDL_RenderCopyEx(renderer, target->tex, NULL, &dstRect, 0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Graphics::present() {
	SDL_RenderPresent(renderer);
}