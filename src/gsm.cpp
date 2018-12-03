
#include "include/gsm.h"

bool pause;	//Is the game paused
int tempScreen; //What was the room before you paused?

std::string GSM::globalScreen = "neighborhood";

// Game state manager 
GSM::GSM(){
	curScreen = "neighborhood";	// Should describe this here 
	
	pause = false;
	running = false;		// does this refer to the game running bool? its own from GSM.h
}

// Initialize GSM 
void GSM::init(SDL_Renderer* reference){
	std::cout << "Init GSM" << std::endl;

	//When Objects need to load their sprites, they will be passed this renderer
	//As a reference for their init method.
	rendererReference = reference;

	//Init player
	SDL_Rect prect = {2*TILE_SIZE,6*TILE_SIZE,TILE_SIZE,TILE_SIZE};
	Player *p = new Player(prect);
	p->init(reference);

	//Init Screens
	Zone *level_one = new Zone("neighborhood");
	screens["neighborhood"] = level_one;
	
	screens[curScreen]->init(reference);
	running = true;
}

// Update the GSM state 
void GSM::update(Uint32 ticks){
	//previousScreen = GSM::currentScreen;
	if(curScreen.compare(GSM::globalScreen) != 0) {
		std::cout << "screen changed to : " << GSM::globalScreen << std::endl;
	}

	screens[curScreen]->update(ticks);
	
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
	
	renderer = screens[curScreen]->draw(renderer);
	
	return renderer;	
}

// 
void GSM::input(const Uint8* keystate){

	screens[curScreen]->input(keystate);
}
