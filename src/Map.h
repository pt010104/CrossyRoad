#ifndef CBIRD2_H
#define CBIRD2_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "SpriteLoader.h"
#include "TextureManager.h"

class Map{
private:
    int numFrames; 
public:
    Map();
    Map(int width, float startX, float startY);
    void Gen();    
};

#endif