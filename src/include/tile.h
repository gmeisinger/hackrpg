#ifndef BANDCAMP_TILE_H_
#define BANDCAMP_TILE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>
#include <vector>

class Tile
{
private:
	SDL_Rect srcRect;
	SDL_Rect destRect;
	std::unordered_map<std::string, std::string> properties;
	bool blocking;
	bool door;
	bool active;
public:
	Tile(SDL_Rect _srcRect);
	Tile();
	Tile(const Tile& t);
	Tile(Tile *t);
	SDL_Rect* getSource();
	SDL_Rect* getDest();
	void setDest(SDL_Rect rect);
	bool isBlocking();
	void setBlocking(bool b);
	bool isDoor();
	void setDoor(bool b);
	void toggleBlocking();
	bool isActive();
	void addProperty(std::string key, std::string val);
	std::string getProperty(std::string key);
	std::unordered_map<std::string,std::string> getProperties();
};

#endif // BANDCAMP_TILE_H_