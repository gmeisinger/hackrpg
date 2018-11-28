
#include "include/tilemap.h"

//constructor
Tilemap::Tilemap() {
	srand(time(NULL));
}

/* Summary
 * Argument  
 *
*/
Tilemap::Tilemap(std::string fname) {
	jsonfile = fname;
	srand(time(NULL));
}

//destructor
Tilemap::~Tilemap() {

}


//returns the map as 2d vector
std::vector<std::vector< std::vector < Tile* >>> Tilemap::getMap() {
	return map;
}

std::vector<std::vector< std::vector < Tile* >>>& Tilemap::getMapRef() {
	std::vector<std::vector< std::vector < Tile* >>>& mapref = map;
	return mapref;
}

void Tilemap::setWidth(int w) {
	width = w;
}

void Tilemap::setHeight(int h) {
	height = h;
}

//setup tiles
void Tilemap::init(SDL_Renderer* reference) {
	parseTiledMap(reference, jsonfile);
}

//draw the tiles
SDL_Renderer* Tilemap::draw(SDL_Renderer* render, SDL_Rect cam) {
	for(auto layer : map) {
		for(int row=0;row<height;row++) {
			for(int col=0;col<width;col++) {

				if(layer[row][col]->isActive() && (col*TILE_SIZE - cam.x >= -TILE_SIZE) && (row*TILE_SIZE - cam.y >= -TILE_SIZE)) {
					Tile* t = layer[row][col];
					SDL_Rect* src = t->getSource();
					SDL_Rect dest = {(col*TILE_SIZE) - cam.x, (row*TILE_SIZE) - cam.y, TILE_SIZE, TILE_SIZE};
					SDL_RenderCopy(render, tileset.getImage(), src, &dest);
				}
			}
		}
	}
	
	return render;
}

std::vector<std::vector<Tile*>> Tilemap::convert( std::vector<std::vector<int>> intmap) {


}

std::vector<std::vector<Tile*>> Tilemap::convert( std::vector<int> intmap) {
	std::vector<std::vector<Tile*>> ret = std::vector<std::vector<Tile*>>(height, std::vector<Tile*>(width, new Tile()));
	for(int i=0;i<intmap.size();i++) {
		Tile *src_tile = tileset.get(intmap[i]);
		Tile *t = new Tile(src_tile);
		int row = i / width;
		int col = i % width;
		//std::cout << "(" << row << "," << col << ")" << i << std::endl;
		ret[row][col] = t;
	}
	return ret;
}


void Tilemap::addLayer(std::vector<std::vector<Tile*>> layer) {
	map.push_back(layer);
}

void Tilemap::parseTiledMap(SDL_Renderer* reference, std::string fname) {
	
	JSONReader reader = JSONReader();
	reader.readFile(fname);
	auto string_map = reader.getAttributes();
	auto layer_data = reader.parseMapVec(string_map["layers"]);
	auto tileset_data = reader.parseMapVec(string_map["tilesets"]);
	
	//get tileset info
	for(auto ts_string_map : tileset_data) {
		std::string fname = "res/" + reader.parseFilename(ts_string_map["image"]);
		int imgWidth = reader.parseInt(ts_string_map["imagewidth"]);
		int imgHeight = reader.parseInt(ts_string_map["imageheight"]);
		int tWidth = reader.parseInt(ts_string_map["tilewidth"]);
		int tHeight = reader.parseInt(ts_string_map["tileheight"]);
		int cols = reader.parseInt(ts_string_map["columns"]);
		int count = reader.parseInt(ts_string_map["tilecount"]);
		Tileset ts = Tileset(fname);
		ts.init(reference, imgWidth, imgHeight, tWidth, tHeight, cols, count);
		//get tile properties
		auto tiles = reader.parseMapVec(ts_string_map["tiles"]);
		for(auto tile : tiles) {
			int id = reader.parseInt(tile["id"]);
			auto properties = reader.parseMapVec(tile["properties"]);
			for(auto p : properties) {
				std::string key = reader.parseString(p["name"]);
				std::string val = reader.parseString(p["value"]);
				ts.addProperty(id, key, val);
			}
		}
		tileset = ts;			//Not Complete!
	}

	//std::cout << layer_data.size() << std::endl;

	//get layer data
	for(auto layer_string_map : layer_data) {
		std::vector<int> data = reader.parseIntVec(layer_string_map["data"]);
		//std::cout << layer_string_map["data"] << std::endl;
		setWidth(reader.parseInt(layer_string_map["width"]));
		setHeight(reader.parseInt(layer_string_map["height"]));
		addLayer(convert(data));
	}
}