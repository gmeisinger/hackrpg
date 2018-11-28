
#ifndef HACKER_TILEMAP_H_
#define HACKER_TILEMAP_H_

#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "tile.h"
#include "object.h"
#include "global.h"
#include "jsonreader.h"
#include "tileset.h"

class Tilemap
{
private:
	//SDL_Texture* image;
	std::string jsonfile;
	Tileset tileset;
	int width;
	int height;
	int tileHeight;
	int tileWidth;
	std::vector<std::vector< std::vector < Tile* >>> map;
	//int cur_width;
	//int cur_height;
public:
	Tilemap(std::string fname);
	Tilemap();
	~Tilemap();
	std::vector<std::vector< std::vector < Tile* >>> getMap();
	std::vector<std::vector< std::vector < Tile* >>>& getMapRef();
	//void setMap(std::vector<std::vector< std::vector < int > > > _map);
	void init(SDL_Renderer* reference);
	SDL_Renderer* draw(SDL_Renderer* render, SDL_Rect cam);
	std::vector<std::vector<Tile*>> convert(std::vector<std::vector<int>> intmap);
	std::vector<std::vector<Tile*>> convert(std::vector<int> intmap);
	void addLayer(std::vector<std::vector<Tile*>> layer);
	void parseTiledMap(SDL_Renderer* reference, std::string fname);
	void setWidth(int w);
	void setHeight(int h);
};

#endif  // HACKER_TILEMAP_H_
