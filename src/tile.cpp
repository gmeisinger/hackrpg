#include "include/tile.h"

Tile::Tile(SDL_Rect _srcRect) {
	srcRect = _srcRect;
	
	blocking = false;
	door = false;
	active = true;
}

Tile::Tile() {
	srcRect = {0,0,0,0};
	destRect = {0,0,0,0};
	blocking = false;
	door = false;
	active = false;
}

Tile::Tile(const Tile& t) {
	this->srcRect = t.srcRect;
	this->active = t.active;
	this->blocking = t.blocking;
	this->door = t.door;
	this->properties = t.properties;
	this->id = t.id;
}

void Tile::setId(int i) {
	id = i;
}

int Tile::getId() {
	return id;
}

SDL_Rect* Tile::getSource() {
	return &srcRect;
}

SDL_Rect* Tile::getDest() {
	return &destRect;
}

void Tile::setDest(SDL_Rect rect) {
	srcRect.x = rect.x;
	srcRect.y = rect.y;
	srcRect.w = rect.w;
	srcRect.h = rect.h;
}

bool Tile::hasProperty(std::string prop) {
	auto found = properties.find(prop);
	if(found == properties.end()) {
		return false;
	}
	else {
		return true;
	}
}

bool Tile::isBlocking() {
	return blocking;
}

void Tile::setBlocking(bool b) {
	blocking = b;
}

bool Tile::isDoor() {
	return door;
}

void Tile::setDoor(bool b) {
	door = b;
}

void Tile::toggleBlocking() {
	if(blocking) blocking = false;
	else blocking = true;
}

bool Tile::isActive() {
	return active;
}

void Tile::addProperty(std::string key, std::string val) {
	properties[key] = val;
}

std::string Tile::getProperty(std::string key) {
	return properties[key];
}

std::unordered_map<std::string,std::string> Tile::getProperties() {
	return properties;
}

void Tile::printProperties() {
	std::cout << "Tile: " << id << std::endl;
	for(auto kv : properties) {
		std::cout << kv.first << "  " << kv.second << std::endl;
	}
}