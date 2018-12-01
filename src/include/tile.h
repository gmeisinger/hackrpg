#ifndef BANDCAMP_TILE_H_
#define BANDCAMP_TILE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

class Tile
{
private:
	SDL_Rect srcRect;
	SDL_Rect destRect;
	std::unordered_map<std::string, std::string> properties;
	int id;
	bool blocking;
	bool door;
	bool active;
public:
	Tile(SDL_Rect _srcRect);
	Tile();
	Tile(const Tile& t);
	SDL_Rect* getSource();
	SDL_Rect* getDest();
	void setId(int i);
	int getId();
	void setDest(SDL_Rect rect);
	bool hasProperty(std::string prop);
	bool isBlocking();
	void setBlocking(bool b);
	bool isDoor();
	void setDoor(bool b);
	void toggleBlocking();
	bool isActive();
	void addProperty(std::string key, std::string val);
	std::string getProperty(std::string key);
	std::unordered_map<std::string,std::string> getProperties();
	void printProperties();
};

#endif // BANDCAMP_TILE_H_