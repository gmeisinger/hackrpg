/* Team Bandcamp
 * Class function: 
 * 
*/
#include "include/player.h"
#include "include/game.h"
#include "include/collision.h"
#include "include/spritesheet.h"

constexpr int MAX_SPEED = 3;
constexpr int BORDER_SIZE = 32;
constexpr int SHORTEN_DIST = 8;

SDL_Rect playerRect;
SDL_Rect hitRect;
SDL_Rect* frame;
SpriteSheet sheet;
std::unordered_map<std::string, Animation*> anims;
Animation* anim;
int x_deltav;
int y_deltav;
int x_vel;
int y_vel;

//Constructor - takes a texture, width and height
Player::Player(SDL_Rect _rect) {
    playerRect = _rect;
    hitRect = {playerRect.x + 2*SHORTEN_DIST, playerRect.y +SHORTEN_DIST, playerRect.w - 4*SHORTEN_DIST, playerRect.h - SHORTEN_DIST};
    x_deltav = 0;
    y_deltav = 0;
    x_vel = 0;
    y_vel = 0;

	up = false;
	down = false;
	left = false;
	right = false;
	space = false;

    player = this;
}

//
Player::Player(){}

//destructor
Player::~Player() {

}

//
std::string Player::getInstanceName(){
	return "player"; //There should only be one instance in the current room
}

/* Summary
 * Argument  
 *
*/
void Player::init(SDL_Renderer* gRenderer){
	rendererReference = gRenderer;
	
	//set up player animations
	setSpriteSheet(utils::loadTexture(gRenderer, "res/player-large.png"), 36, 1);

    addAnimation("left", new Animation(getSheet().getRange(0,3)));
    addAnimation("right", new Animation(getSheet().getRange(5,8)));
    addAnimation("down", new Animation(getSheet().getRange(10,13)));
	addAnimation("up", new Animation(getSheet().getRange(15,18)));
	
	setAnimation("down");

}

/* Summary
 * Argument  
 *
*/
void Player::setSpriteSheet(SDL_Texture* _sheet, int _cols, int _rows) {
    sheet = SpriteSheet(_sheet);
    sheet.setClips(_cols, _rows, playerRect.w, playerRect.h);
}

/* Summary
 * Argument  
 *
*/
SpriteSheet Player::getSheet() {
    return sheet;
}

/* Summary
 * Argument  
 *
*/
void Player::addAnimation(std::string tag, Animation *anim) {
    anims[tag] = anim;
}

/* Summary
 * Argument  
 *
*/
Animation* Player::getAnimation(std::string tag) {
    return anims[tag];
}

/* Summary
 * Argument  
 *
*/
void Player::setAnimation(std::string tag) {
    anim = anims[tag];
}

//returns width of Player
int Player::getWidth() {
    return playerRect.w;
}

//returns height of Player
int Player::getHeight() {
    return playerRect.h;
}

//returns x position of Player
int Player::getX() {
    return playerRect.x;
}

//returns y position of Player
int Player::getY() {
    return playerRect.y;
}

//
SDL_Rect* Player::getRect() {
    return &playerRect;
}

SDL_Rect* Player::getHitRect() {
    return &hitRect;
}

/* Summary
 * Argument  
 *
*/
void Player::updateVelocity(int _xdv, int _ydv) {
    // If we dont want out dot to be in a frictionless vacuum...
    if (_xdv == 0) {
        // No user-supplied "push", return to rest
        if (x_vel > 0)
            _xdv = -1;
        else if (x_vel < 0)
            _xdv = 1;
    }
    if (_ydv == 0) {
        if (y_vel > 0)
            _ydv = -1;
        else if (y_vel < 0)
            _ydv = 1;
    }
    
    // Speed up/slow down
    x_vel += _xdv;
    y_vel += _ydv;

    // Check speed limits
    if (x_vel < -1 * MAX_SPEED)
        x_vel = -1 * MAX_SPEED;
    else if (x_vel > MAX_SPEED)
        x_vel = MAX_SPEED;

    if (y_vel < -1 * MAX_SPEED)
        y_vel = -1 * MAX_SPEED;
    else if (y_vel > MAX_SPEED)
        y_vel = MAX_SPEED;

}

// 
void Player::updatePosition() {
    playerRect.x += x_vel;
    playerRect.y += y_vel;
    hitRect.x += x_vel;
    hitRect.y += y_vel;
}

/* Summary
 * Argument  
 *
*/
void Player::checkBounds(int max_width, int max_height) {
    if (playerRect.x < BORDER_SIZE)
        playerRect.x = BORDER_SIZE;
    else if (playerRect.x + playerRect.w > max_width - BORDER_SIZE)
        playerRect.x = max_width - playerRect.w - BORDER_SIZE;

    if (playerRect.y < BORDER_SIZE)
        playerRect.y = BORDER_SIZE;
    else if (playerRect.y + playerRect.h > max_height - BORDER_SIZE)
        playerRect.y = max_height - playerRect.h - BORDER_SIZE;
}

/* Summary
 * Argument  
 *
*/

void Player::updateAnimation(Uint32 ticks) {
    if(x_vel == 0 && y_vel == 0) {
        anim->reset();
        anim->stop();
    }
    else if(x_vel > 0 && std::abs(x_vel) > std::abs(y_vel)) {
        setAnimation("right");
        anim->play();
    }
    else if(x_vel < 0 && std::abs(x_vel) > std::abs(y_vel)) {
        setAnimation("left");
        anim->play();
    }
    else if(y_vel > 0 && std::abs(y_vel) > std::abs(x_vel)) {
        setAnimation("down");
        anim->play();
    }
    else if(y_vel < 0 && std::abs(y_vel) > std::abs(x_vel)) {
        setAnimation("up");
        anim->play();
    }
    anim->update(ticks);
}

void Player::update(std::unordered_map<std::string, Object*> &objectList, std::vector<std::vector<std::vector<Tile*>>> &grid, Uint32 ticks) {

	int x_deltav = 0;
	int y_deltav = 0;
    
    //Get the position of the player before they move
    //Needed for collision detection
    int curX = playerRect.x;
    int curY = playerRect.y;

	if (up)
		y_deltav -= 1;
	if (left)
		x_deltav -= 1;
	if (down)
		y_deltav += 1;
	if (right)
		x_deltav += 1;

	updateVelocity(x_deltav, y_deltav);

    //Checks if you are overlapping an enemy, slows down velocity if you are
    //checkEnemy(x_deltav, y_deltav);

    //update animation
    updateAnimation(ticks);

	// Move box
	updatePosition();

    //Check you haven't collided with object
    checkCollision(curX, curY, grid);
	
}

/* Summary
 * Argument  
 *
*/

void Player::input(const Uint8* keystate) {
	up = keystate[SDL_SCANCODE_W];
	left = keystate[SDL_SCANCODE_A];
	down = keystate[SDL_SCANCODE_S];
	right = keystate[SDL_SCANCODE_D];
	space = keystate[SDL_SCANCODE_SPACE];
}

/* Summary
 * Argument  
 *
*/
SDL_Renderer* Player::draw(SDL_Renderer* renderer, SDL_Rect cam) {
    SDL_Rect* dest = new SDL_Rect;
    *dest = playerRect;
    dest->x -= cam.x;
    dest->y -= cam.y;
    SDL_RenderCopy(renderer, sheet.getTexture(), anim->getFrame(), dest);
	
	return renderer;
}

/* Summary
 * Argument  
 *
*/
bool Player::isUsed() {
    return false;
}


void Player::checkCollision(int curX, int curY, std::vector<std::vector<std::vector<Tile*>>> &grid) {
    int nx = hitRect.x/TILE_SIZE;
    int ny = hitRect.y/TILE_SIZE;
    for(auto layer : grid) {
        layer[ny][nx]->printProperties();
    }
    if(collision::checkColLeft(hitRect, grid, TILE_SIZE) || collision::checkColRight(hitRect, grid, TILE_SIZE)) {
        playerRect.x = curX;
        hitRect.x = curX + 2*SHORTEN_DIST;
    }
    
    if(collision::checkColTop(hitRect, grid, TILE_SIZE) || collision::checkColBottom(hitRect, grid, TILE_SIZE)) {
        playerRect.y = curY;
        hitRect.y = curY+SHORTEN_DIST;

        playerRect.x += x_vel;
        hitRect.x += x_vel;

        y_vel = 0;
        if(collision::checkColLeft(hitRect, grid, TILE_SIZE) || collision::checkColRight(hitRect, grid, TILE_SIZE)) {
            x_vel = 0; 
            playerRect.x = curX;
            hitRect.x = curX + 2*SHORTEN_DIST;   

        }
    }
    
}
