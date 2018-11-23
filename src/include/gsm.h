<<<<<<< HEAD
#ifndef BANDCAMP_GSM_H_
#define BANDCAMP_GSM_H_
=======
#ifndef HACKER_GSM_H_
#define HACKER_GSM_H_
>>>>>>> 62b64b920be81f85205c3d5be546fb8871f510ef

#include <SDL.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <SDL_image.h>
#include "screen.h"

class GSM {
	private:
		std::vector<Screen*> screens;
		int previousScreen; //To check if we changed rooms
		bool running;
		SDL_Renderer* rendererReference;
	public:
		
		GSM();
		//~GSM();
		static int currentScreen;
		static void setCurrentScreen(int newScreen);
		void init(SDL_Renderer *renderer);
		void input(const Uint8* keystate);
		void update(Uint32 ticks);
		SDL_Renderer* draw(SDL_Renderer *renderer);

};

#endif	//	HACKER_GSM_H_
