#include "include/tileset.h"

Tileset::Tileset() {

}

Tileset::Tileset(std::string _filename) {
	filename = _filename;
}

void Tileset::init(SDL_Renderer* reference) {
	image = utils::loadTexture(reference, filename);
	std::cout << "count : " << tileCount << std::endl;
	for(int i=0;i<tileCount;i++) {
		int index = i + 1;
		int row = i / columns;
		int col = i % columns;
		SDL_Rect rect = {col * tileWidth, row * tileHeight, tileWidth, tileHeight};
		tiles[index] = new Tile(rect);
		tiles[index]->setId(i);

	}
	tiles[0] = new Tile();
	tiles[0]->setId(0);
}

void Tileset::init(SDL_Renderer* reference, int imgWidth, int imgHeight, int tWidth, int tHeight, int cols, int count) {
	imageWidth = imgWidth;
	imageHeight = imgHeight;
	tileWidth = tWidth;
	tileHeight = tHeight;
	columns = cols;
	tileCount = count;
	init(reference);
}

void Tileset::setImageWidth(int w) {
	imageWidth = w;
}

void Tileset::setImageHeight(int h) {
	imageHeight = h;
}

void Tileset::setTileWidth(int w) {
	tileWidth = w;
}

void Tileset::setTileHeight(int h) {
	tileHeight = h;
}

void Tileset::setCols(int c) {
	columns = c;
}

void Tileset::setCount(int c) {
	tileCount = c;
}

void Tileset::addProperty(int id, std::string key, std::string val) {
	int index = id + 1;
	tiles[index]->addProperty(key, val);
}

Tile* Tileset::get(int i) {
	
	Tile* t =  tiles[i];
	return t;
}

SDL_Texture* Tileset::getImage() {
	return image;
}

void Tileset::printIDs() {
	for ( auto kv : tiles ) {
		std::cout << kv.first << " : " << kv.second->getId() << std::endl;
		for(auto prop : kv.second->getProperties()) {
			std::cout << "	" << prop.first << " : " << prop.second << std::endl;
		}
	}
}