
#ifndef HACKER_ZONE_H_
#define HACKER_ZONE_H_

#include <SDL.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "screen.h"
#include "object.h"
#include "tilemap.h"
#include "player.h"

extern int currentScreen;

class Zone : public Screen
{
    private:
    	bool start;
    	std::string map_file;
		SDL_Renderer* rendererReference;
		Tilemap tilemap;
		std::unordered_map<std::string, Object*> objectList;
    public:
    	Zone();
    	Zone(std::string mfile);
    	SDL_Rect camera;
		void init(SDL_Renderer* renderer);
		void input(const Uint8* keystate);
		void update(Uint32 ticks);
		SDL_Renderer* draw(SDL_Renderer * renderer);
		//EXIT METHOD??

};

#endif  //  HACKER_ZONE_H_
