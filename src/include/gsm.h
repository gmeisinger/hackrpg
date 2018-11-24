
#ifndef HACKER_GSM_H_
#define HACKER_GSM_H_

#include <SDL.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL_image.h>
#include "screen.h"
#include "zone.h"
#include "player.h"

class GSM {
	private:
		std::unordered_map<std::string,Screen*> screens;
		int previousScreen; //To check if we changed rooms
		bool running;
		SDL_Renderer* rendererReference;
		//Player *p;
	public:
		
		GSM();
		//~GSM();
		std::string curScreen;
		
		void init(SDL_Renderer *renderer);
		void input(const Uint8* keystate);
		void update(Uint32 ticks);
		SDL_Renderer* draw(SDL_Renderer *renderer);

};

#endif	//	HACKER_GSM_H_
