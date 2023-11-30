#pragma once

#include <SDL2/SDL.h>

struct image_t {
	int w; int h;
	SDL_Texture *tex;
};

image_t *imageLoad (const char *path, SDL_Renderer *renderer);
void imageDraw (SDL_Renderer *rnd, image_t *target, int posX, int posY, bool flip = false);

class Graphics {
	private:
		SDL_Renderer* renderer;
		Graphics() = default;
	public:
		static Graphics* init(SDL_Window *window);
		image_t *loadImage(const char *path);
		void drawImageFullscreen(image_t *target);
		void drawImage(image_t *target, int posX, int posY, bool flip = false);
		void present();
};