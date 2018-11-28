#ifndef HACKER_TILESET_H_
#define HACKER_TILESET_H_

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <string>
#include "tile.h"
#include "global.h"

class Tileset
{
private:
    SDL_Texture* image;
    std::unordered_map<int, Tile*> tiles;
    std::string filename;
    int imageWidth;
    int imageHeight;
    int tileWidth;
    int tileHeight;
    int tileCount;
    int columns;
public:
    Tileset();
    Tileset(std::string _filename);
    void init(SDL_Renderer* reference);
    void init(SDL_Renderer* reference, int imgWidth, int imgHeight, int tileWidth, int tileHeight, int cols, int count);
    void setImageWidth(int w);
    void setImageHeight(int h);
    void setTileWidth(int w);
    void setTileHeight(int h);
    void setCols(int c);
    void setCount(int c);
    void addProperty(int index, std::string key, std::string val);
    Tile* get(int i);
    SDL_Texture* getImage();
};

#endif  //  HACKER_TILESET_H_
