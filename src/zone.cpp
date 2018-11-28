#include "include/zone.h"

Zone::Zone() {
}

void Zone::init(SDL_Renderer* reference) {

	objectList["player"] = player;

	rendererReference = reference;

	tilemap = Tilemap("res/zones/testarea.json");
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
	//draw map before objects
	tilemap.draw(renderer, camera);
	//draw objects
	std::unordered_map<std::string, Object*>::iterator it = objectList.begin();
	while(it != objectList.end()){
		renderer = it->second->draw(renderer, camera);
		it++;
	}
	return renderer;
}