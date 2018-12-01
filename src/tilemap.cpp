
#include "include/tilemap.h"

std::string TILESET_PATH = "res/tiles.json";

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
		Tile *t = new Tile(*src_tile);
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

void Tilemap::parseTileset(SDL_Renderer* reference, std::string fname) {
	JSONReader reader = JSONReader();
	reader.readFile(fname);
	auto tileset_data = reader.getAttributes();
	//get metadata

	std::string img_fname = "res/" + reader.parseString(tileset_data["image"]);
	int imgWidth = reader.parseInt(tileset_data["imagewidth"]);
	int imgHeight = reader.parseInt(tileset_data["imageheight"]);
	int tWidth = reader.parseInt(tileset_data["tilewidth"]);
	int tHeight = reader.parseInt(tileset_data["tileheight"]);
	int cols = reader.parseInt(tileset_data["columns"]);
	int count = reader.parseInt(tileset_data["tilecount"]);
	Tileset ts = Tileset(img_fname);
	ts.init(reference, imgWidth, imgHeight, tWidth, tHeight, cols, count);

	//individual tile data
	auto tile_data = reader.parseMapVec(tileset_data["tiles"]);
	for( auto tile : tile_data) {
		int id = reader.parseInt(tile["id"]);
		auto properties = reader.parseMapVec(tile["properties"]);
		for( auto p : properties) {
			std::string key = reader.parseString(p["name"]);
			std::string val = reader.parseString(p["value"]);
			ts.addProperty(id, key, val);
		}
	}
	tileset = ts;
	tileset.printIDs();
}

void Tilemap::parseTiledMap(SDL_Renderer* reference, std::string fname) {
	
	JSONReader reader = JSONReader();
	reader.readFile(fname);
	auto string_map = reader.getAttributes();
	auto layer_data = reader.parseMapVec(string_map["layers"]);


	auto tileset_data = reader.parseMapVec(string_map["tilesets"]);
	
	parseTileset(reference, TILESET_PATH);
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