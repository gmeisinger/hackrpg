#include "include/collision.h"

//Collision detection for two rectangles
bool collision::checkCol(SDL_Rect rect1, SDL_Rect rect2) {    
    //Vertical overlap 
    if(rect1.y + rect1.h <= rect2.y)
    {
        return false;
    }
    if(rect1.y >= rect2.y + rect2.h)
    {
        return false;
    }

    //Horizontal overlap
    if(rect1.x + rect1.w <= rect2.x)
    {
        return false;
    }
    if(rect1.x >= rect2.x + rect2.w)
    {
        return false;
    }

    return true;
}



//Collision detection for a rect and the walls of a tilemap
bool collision::checkColTop(SDL_Rect rect, std::vector<std::vector<Tile*>> &grid, int tilesize) {
    //which tiles are we in?
    int normLeftX = rect.x/tilesize;
    int normY = rect.y/tilesize;
    int normRightX = (rect.x + rect.w)/tilesize;
    

    Tile *tileL = grid[normY][normLeftX];
    Tile *tileR = grid[normY][normRightX];
    if(tileL->isBlocking() || tileR->isBlocking()) {
        return true;
    }
    else {
        return false;
    }
}

// add description
bool collision::checkColBottom(SDL_Rect rect, std::vector<std::vector<Tile*>> &grid, int tilesize) {
    //which tiles are we in?
    int normLeftX = rect.x/tilesize;
    int normY = (rect.y + rect.h)/tilesize;
    int normRightX = (rect.x + rect.w)/tilesize;

    Tile *tileL = grid[normY][normLeftX];
    Tile *tileR = grid[normY][normRightX];
    if(tileL->isBlocking() || tileR->isBlocking()) {
        return true;
    }
    else {
        return false;
    }
}

//Collision detection for a rect and the walls of a tilemap
bool collision::checkColLeft(SDL_Rect rect, std::vector<std::vector<int>> grid, int tilesize) {
    //which tiles are we in?
    int normX = rect.x/tilesize;
    int normTopY = rect.y/tilesize;
    int normBottomY = (rect.y + rect.h)/tilesize;
    
    Tile *tileT = grid[normTopY][normX];
    Tile *tileB = grid[normBottomY][normX];
    if(tileT->isBlocking() || tileB->isBlocking()) {
        return true;
    }
    else {
        return false;
    }
}

// add description
bool collision::checkColRight(SDL_Rect rect, std::vector<std::vector<int>> grid, int tilesize) {
    //which tiles are we in?
    int normX = (rect.x + rect.w)/tilesize;
    int normTopY = rect.y/tilesize;
    int normBottomY = (rect.y + rect.h)/tilesize;
    

    Tile *tileT = grid[normTopY][normX];
    Tile *tileB = grid[normBottomY][normX];
    if(tileT->isBlocking() || tileB->isBlocking()) {
        return true;
    }
    else {
        return false;
    }
}