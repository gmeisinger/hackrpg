#ifndef HACKER_PLAYER_H_
#define HACKER_PLAYER_H_

#include <SDL.h>
#include <unordered_map>
#include <cmath>
#include <string>
#include <vector>

#include "object.h"
#include "spritesheet.h"
#include "animation.h"
#include "global.h"

class Player : public Object
{
    private:
        SDL_Rect playerRect;
        SDL_Rect hitRect;
        int x_deltav;
        int y_deltav;
        int x_vel;
        int y_vel;
		int cooldownTicks;
	    bool up;
	    bool down;
	    bool left;
	    bool right;
		bool space;
	    SpriteSheet sheet;
        std::unordered_map<std::string, Animation> anims;
        Animation* anim;
		SDL_Renderer* rendererReference;
		
    public:
        Player(SDL_Rect _rect);
		Player();
        ~Player();
		    std::string getInstanceName();
		    void init(SDL_Renderer* gRenderer);
		    void update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<Tile*>> &grid, Uint32 ticks);
		    void input(const Uint8* keystate);
		    SDL_Renderer* draw(SDL_Renderer* gRenderer, SDL_Rect cam);
		    void setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows);
        void updateVelocity(int _xdv, int _ydv);
        void updatePosition();
        void checkCollision(int curX, int curY, std::vector<std::vector<Tile*>> &grid);
        int getWidth();
        int getHeight();
        int getX();
        int getY();
        SDL_Rect* getRect();
        void addAnimation(std::string tag, Animation anim);
        Animation* getAnimation(std::string tag);
        void setAnimation(std::string tag);
        void updateAnimation(Uint32 ticks);
        SpriteSheet getSheet();
        bool isUsed();
};

#endif  //  HACKER_PLAYER_H_
