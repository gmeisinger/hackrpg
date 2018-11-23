#include "include/zone.h"

Zone::Zone() {

}

void Zone::init() {
	objectList["player"] = player;

	rendererReference = reference;

	tilemap = Tilemap(utils::loadTexture(reference, "res/tiles.png"), 40, 40);
	tilemap.init();
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
	camera.x = p.getX() - (camera.w/2);
	camera.y = p.getY() - (camera.h/2);
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