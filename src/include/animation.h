
#ifndef HACKER_ANIMATION_H_
#define HACKER_ANIMATION_H_

#include <SDL.h>
#include <vector>

class Animation
{
	private:
		std::vector< SDL_Rect > frames;
		int curFrame;
		Uint32 frameTicks;
		bool playing;
		bool loop;
		
	public:
		bool playedOnce;
		Animation(std::vector<SDL_Rect> _frames);
		Animation(std::vector<SDL_Rect> _frames, bool _loop);
		Animation(SDL_Rect *); //One Frame
		Animation();
		~Animation();
		void update(Uint32 ticks);
		void play();
		void stop();
		void reset();
		SDL_Rect* getFrame();
		int getCurFrame();
		std::vector< SDL_Rect >* getFrames();
		void setFrame(int _frame);
};

#endif  //  HACKER_ANIMATION_H_
