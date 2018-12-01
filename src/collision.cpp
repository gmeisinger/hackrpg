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
bool collision::checkColTop(SDL_Rect rect, std::vector<std::vector<std::vector<Tile*>>> &grid, int tilesize) {
    bool ret = false;
    //which tiles are we in?
    int normLeftX = rect.x/tilesize;
    int normY = rect.y/tilesize;
    int normRightX = (rect.x + rect.w)/tilesize;

    std::string tileids = "";
    std::vector<int> ids;
    
    for(auto layer : grid) {
        Tile *tileL = layer[normY][normLeftX];
        Tile *tileR = layer[normY][normRightX];
        //std::cout << std::string( 100, '\n' );
        //tileL->printProperties();
        //tileR->printProperties();
        ids.push_back(tileL->getId());
        ids.push_back(tileR->getId());
        if(tileL->hasProperty("block") || tileR->hasProperty("block")) {
            return true;
        }
    }
    /*std::cout << std::string( 100, '\n' );
    for(auto id : ids) {
        std::cout << id << std::endl;
    }*/
    return ret;
}

// add description
bool collision::checkColBottom(SDL_Rect rect, std::vector<std::vector<std::vector<Tile*>>> &grid, int tilesize) {
    bool ret = false;
    //which tiles are we in?
    int normLeftX = rect.x/tilesize;
    int normY = (rect.y + rect.h)/tilesize;
    int normRightX = (rect.x + rect.w)/tilesize;

    //std::cout << std::string( 100, '\n' );
    for(auto layer : grid) {
        Tile *tileL = layer[normY][normLeftX];
        Tile *tileR = layer[normY][normRightX];

        //std::cout << "layer : " << l++ << std::endl;
        
        //tileL->printProperties();
        //tileR->printProperties();
        if(tileL->hasProperty("block") || tileR->hasProperty("block")) {
            return true;
        }
    }
    return ret;
}

//Collision detection for a rect and the walls of a tilemap
bool collision::checkColLeft(SDL_Rect rect, std::vector<std::vector<std::vector<Tile*>>> &grid, int tilesize) {
    bool ret = false;
    //which tiles are we in?
    int normX = rect.x/tilesize;
    int normTopY = rect.y/tilesize;
    int normBottomY = (rect.y + rect.h)/tilesize;
    
    for(auto layer : grid) {
        Tile *tileT = layer[normTopY][normX];
        Tile *tileB = layer[normBottomY][normX];

        //std::cout << std::string( 100, '\n' );
        //tileT->printProperties();
        //tileB->printProperties();
        if(tileT->hasProperty("block") || tileB->hasProperty("block")) {
            return true;
        }
    }
    return ret;
}

// add description
bool collision::checkColRight(SDL_Rect rect, std::vector<std::vector<std::vector<Tile*>>> &grid, int tilesize) {
    bool ret = false;
    //which tiles are we in?
    int normX = (rect.x + rect.w)/tilesize;
    int normTopY = rect.y/tilesize;
    int normBottomY = (rect.y + rect.h)/tilesize;
    
    for(auto layer : grid) {
        Tile *tileT = layer[normTopY][normX];
        Tile *tileB = layer[normBottomY][normX];

        //std::cout << std::string( 100, '\n' );
        //tileT->printProperties();
        //tileB->printProperties();
        if(tileT->hasProperty("block") || tileB->hasProperty("block")) {
            return true;
        }
    }
    return ret;
}