
#include "include/gsm.h"

bool pause;	//Is the game paused
int tempScreen; //What was the room before you paused?

// Game state manager 
GSM::GSM(){
	curScreen = "test";	// Should describe this here 
	
	pause = false;
	running = false;		// does this refer to the game running bool? its own from GSM.h
}

// Initialize GSM 
void GSM::init(SDL_Renderer* reference){
	std::cout << "Init GSM" << std::endl;

	//When Objects need to load their sprites, they will be passed this renderer
	//As a reference for their init method.
	rendererReference = reference;

	SDL_Rect prect = {2*TILE_SIZE,6*TILE_SIZE,TILE_SIZE,TILE_SIZE};
	Player *p = new Player(prect);
	p->init(reference);

	//Init Screens
	Zone *test = new Zone();
	screens["test"] = test;
	
	screens[curScreen]->init(reference);
	running = true;
}

// Update the GSM state 
void GSM::update(Uint32 ticks){
	//previousScreen = GSM::currentScreen;

	screens["test"]->update(ticks);
	
	//Checking if we changed screens this loop
	//If so, then call the init to the new screen.
	/*if(previousScreen != GSM::currentScreen)
	{	
		if(GSM::currentScreen == -1){ //The Pause Command
			pause = true;
			tempScreen = previousScreen;
			pauseMenu.init(rendererReference);
		}
		else if(GSM::currentScreen == -2){ //The Unpause Command
			pause = false;
			GSM::currentScreen = tempScreen;
		}
		else
			screens[GSM::currentScreen]->init(rendererReference);
	}*/
}

// 
SDL_Renderer* GSM::draw(SDL_Renderer *renderer){
	
	renderer = screens["test"]->draw(renderer);
	
	return renderer;	
}

// 
void GSM::input(const Uint8* keystate){

	screens["test"]->input(keystate);
}
