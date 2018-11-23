
#include "include/global.h"

int screen_w = SCREEN_WIDTH;
int screen_h = SCREEN_HEIGHT;
int tile_s = TILE_SIZE;

Player *player;
HUD *hud_g;

//loads image at specified path as a texture
//fname = relative path to image
SDL_Texture* utils::loadTexture(SDL_Renderer* renderer, std::string fname) {
    //the final texture
    SDL_Texture* newTexture = nullptr;
    //load the image
	SDL_Surface* startSurf = IMG_Load(fname.c_str());
	if (startSurf == nullptr) {
		std::cout << "Unable to load image " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}
	//color key
	SDL_SetColorKey(startSurf, SDL_FALSE, SDL_MapRGB(startSurf->format, 0, 0xFF, 0xFF));
    //create texture from image
	newTexture = SDL_CreateTextureFromSurface(renderer, startSurf);
	if (newTexture == nullptr) {
		std::cout << "Unable to create texture!" << std::endl;
	}
    //free original surface
	SDL_FreeSurface(startSurf);

	return newTexture;
}