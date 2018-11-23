
#ifndef HACKER_GAME_H_
#define HACKER_GAME_H_

#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include "gsm.h"


class GSM;

class Game {
	private:
		bool running;
		SDL_Window* gWindow;
		SDL_Renderer* gRenderer;
		GSM * gsm;
	public:
		Game();
		//~Game();
		bool init();
		void run();
		void close();
		void input(const Uint8* keystate);
		void update(Uint32 ticks);
		void draw();
};

#endif	//	HACKER_GAME_H_
