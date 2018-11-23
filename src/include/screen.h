#ifndef HACKER_SCREEN_H_
#define HACKER_SCREEN_H_

#include <SDL.h>
#include <vector>
#include "object.h"

extern int currentScreen;

class Screen
{
    private:
    bool start;
		std::vector<Object*> roomList;
		SDL_Renderer* rendererReference;
		
    public:
    SDL_Rect camera;
		virtual void init(SDL_Renderer* renderer) = 0;
		virtual void input(const Uint8* keystate) = 0;
		virtual void update(Uint32 ticks) = 0;
		virtual SDL_Renderer* draw(SDL_Renderer * renderer) = 0;
};

#endif  //  HACKER_SCREEN_H_