#include <sstream>
#include <iostream>
#include "include/tilemap.h"

//vars
SDL_Texture* image;
std::unordered_map<int, SDL_Rect> tiles;
/*
	0 - 
	1 - 
	2 - 
	3 - 
*/
int width;
int height;
int tilesize;
int cur_width;
int cur_height;
std::vector< std::vector < Tile* > >map;
//constructor
Tilemap::Tilemap() {
	image = nullptr;
	width = 25;
	height = 18;
	tilesize = tile_s;
	cur_width = 0;
	cur_height = 0;
	srand(time(NULL));
}

/* Summary
 * Argument  
 *
*/
Tilemap::Tilemap(SDL_Texture* tex, int _width, int _height, int _tilesize) {
	image = tex;
	width = _width;
	height = _height;
	tilesize = _tilesize;
	cur_width = 0;
	cur_height = 0;
	srand(time(NULL));
}

//destructor
Tilemap::~Tilemap() {

}


//returns the map as 2d vector
std::vector< std::vector < Tile* > > Tilemap::getMap() {
	return map;
}

std::vector< std::vector < Tile* > >& Tilemap::getMapRef() {
	std::vector< std::vector < Tile* > >& mapref = map;
	return mapref;
}

//setup tiles
void Tilemap::init() {
	map = std::vector<std::vector<Tile*>>(height, std::vector<Tile*>(width, new Tile()));
	
	//floor tile
	tiles[1] = {0,0,tilesize,tilesize};

	std::vector<std::vector<int>> testmap = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));
	convert(testmap);
}

//draw the tiles
SDL_Renderer* Tilemap::draw(SDL_Renderer* render, SDL_Rect cam) {
	for(int row=0;row<height;row++) {
		for(int col=0;col<width;col++) {

			if(map[row][col]->isActive() && (col*TILE_SIZE - cam.x >= -TILE_SIZE) && (row*TILE_SIZE - cam.y >= -TILE_SIZE)) {
				Tile* t = map[row][col];
				SDL_Rect* src = t->getSource();
				SDL_Rect dest = {(col*TILE_SIZE) - cam.x, (row*TILE_SIZE) - cam.y, TILE_SIZE, TILE_SIZE};
				SDL_RenderCopy(render, image, src, &dest);
			}
		}
	}
	
	return render;
}

std::vector<std::vector<Tile*>> Tilemap::convert( std::vector<std::vector<int>> intmap) {

	for(int r=0;r<intmap.size();r++) {
		std::cout << std::endl;
		for(int c=0;c<intmap[0].size();c++) {
			std::cout << intmap[r][c];
			if(intmap[r][c] == 1) {
				//floor tile
				map[r][c] = new Tile(tiles[1], {c*tilesize, r*tilesize, tilesize, tilesize});
			}
			else if(intmap[r][c] == 2) {
				// ceiling tile
				map[r][c] = new Tile(tiles[1], {c*tilesize, r*tilesize, tilesize, tilesize});
				map[r][c]->setBlocking(true);
			}
			else if(intmap[r][c] == 3) {
				// wall tile
				map[r][c] = new Tile(tiles[1], {c*tilesize, r*tilesize, tilesize, tilesize});
				map[r][c]->setBlocking(true);
			}
			else if(intmap[r][c] == 4) {
				// DOOR tile
				map[r][c] = new Tile(tiles[1], {c*tilesize, r*tilesize, tilesize, tilesize});
				map[r][c]->setDoor(true);
			}
			else {
				map[r][c] = new Tile();
			}
		}
	}
	return map;

}

void Tilemap::addLayer(std::vector<std::vector<Tile*>> layer) {
	//map.push_back(layer);
}

std::vector<std::vector<Tile*>> Tilemap::parseTiledMap() {
	std::vector<std::vector<Tile*>> layers = {};
	/*PLAN:
	1. get the needed strings by 
		string::size_type position = text.find ("keyword");
		string fragment = text.substr (6, 5);
    		// start at 6, take 5 characters
    		text.erase(5, 5);
    		text.replace(5, 2, "blah");
	*/
}