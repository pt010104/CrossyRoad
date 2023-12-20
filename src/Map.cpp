#include "Map.h"
#include <iostream>
Map::Map()
{}
Map::Map(int width, float startX, float startY)
{
        mX = startX;
        mY = startY;
        numFrames = 8;
        SpriteLoader loader;
        if (!loader.LoadTexture("Assets/Map/Dungeon.png", texture)) {
            std::cerr<<"Failed to load texture";
        }
        if (!loader.LoadAnimations("Assets/Map/Dungeon.json", frames, animations, numFrames)) {
            std::cerr<<"Failed to load Json Map";
        }
        sprite.setTexture(TextureManager::GetTexture("Assets/Animal/Dungeon.png"));
        sprite.setScale(16.625f,16.625f);
            
}
void CBIRD2::Gen()   {
        
}