#ifndef BANDCAMP_GLOBAL_H_
#define BANDCAMP_GLOBAL_H_

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int TILE_SIZE = 32;

extern int screen_w;
extern int screen_h;
extern int tile_s;

class Player;
extern Player *player;

namespace utils
{
    SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string fname);
};

#endif  //  BANDCAMP_GLOBAL_H_
