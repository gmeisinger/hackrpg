#include "include/zone.h"

Zone::Zone() {
	map_file = "res/zones/neighborhood.json";
}

Zone::Zone(std::string mfile) {
	if(mfile.find("res/zones/") == std::string::npos) {
		map_file = "res/zones/" + mfile;
	}
	else map_file = mfile;
	if(map_file.find(".json") == std::string::npos) {
		map_file += ".json";
	}
}

void Zone::init(SDL_Renderer* reference) {

	objectList["player"] = player;

	rendererReference = reference;

	tilemap = Tilemap(map_file);
	tilemap.init(reference);
	camera = {player->getX() - SCREEN_WIDTH/2, player->getY() - SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT};
}
 
void Zone::input(const Uint8* keystate){
		
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		it->second->input(keystate);
		it++;
	}
}

void Zone::update(Uint32 ticks) {
	//
	std::unordered_map<std::string, Object*>& objectListRef = objectList;
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		it->second->update(objectListRef, tilemap.getMapRef(), ticks);
		if(it->second->isUsed()) {
			it = objectList.erase(it);
			break;
		}
		it++;
	}

	//update camera to player position
	camera.x = player->getX() - (camera.w/2);
	camera.y = player->getY() - (camera.h/2);
}

SDL_Renderer* Zone::draw(SDL_Renderer *renderer) {
	//draw first map layer before objects
	tilemap.drawLayer(renderer, camera, 0);
	//draw objects
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		renderer = it->second->draw(renderer, camera);
		it++;
	}
	//draw rest of map
	for(int i=1;i<tilemap.numLayers();i++) {
		tilemap.drawLayer(renderer, camera, i);
	}

	return renderer;
}