#include "include/collision.h"

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