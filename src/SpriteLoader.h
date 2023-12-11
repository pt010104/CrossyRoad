#ifndef SPRITE_LOADER_H
#define SPRITE_LOADER_H

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

struct Frame {
    int x, y, width, height;
};

struct Animation {
    std::vector<Frame> frames;
    float frameDuration;
};

class SpriteLoader {
public:
    static bool LoadTexture(const std::string& texturePath, sf::Texture& texture);
    static bool LoadAnimations(const std::string& jsonPath, std::unordered_map<std::string, Frame>& frames, 
        std::unordered_map<std::string, Animation>& animations);
};

#endif