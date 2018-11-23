#ifndef HACKER_GLOBAL_H_
#define HACKER_GLOBAL_H_

#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int TILE_SIZE = 32;

extern int screen_w;
extern int screen_h;
extern int tile_s;

class Player;
extern Player *player;
class HUD;
extern HUD *hud_g;

namespace utils
{
    SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string fname);
};

#endif  //  HACKER_GLOBAL_H_
