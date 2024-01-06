#include "SpriteLoader.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

bool SpriteLoader::LoadTexture(const std::string& texturePath, sf::Texture& texture) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        return false;
    }
    return true;
}
bool SpriteLoader::LoadAnimations(const std::string& jsonPath, std::unordered_map<std::string, Frame>& frames, 
    std::unordered_map<std::string, Animation>& animations, int numFrames) 
{
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open JSON: " << jsonPath << std::endl;
        return false;
    }
    
    json j;
    file >> j;

    for (auto& el : j["frames"].items()) {
        Frame frame = {
            el.value()["x"],
            el.value()["y"],
            el.value()["width"],
            el.value()["height"]
        };
        frames[el.key()] = frame;
    }
    std::string directions[] = {
        "right", "left", "down", "up", "die", 
        "people_map1", "mons_map1", 
        "people_map2", "mons_map2",
        "people_map3", "mons_map3", 
        "people_map4", "mons_map4", 
        "people_map5", "mons_map5", 
        "fire", "appear", "wall"
    };
    for (const auto& dir : directions) {
        Animation anim;
        anim.frameDuration = 0.1f; 

        for (int i = 1; i <= numFrames; ++i) {
            std::string frameKey = dir + "_" + std::to_string(i);
            if (frames.find(frameKey) != frames.end()) 
                anim.frames.push_back(frames[frameKey]);
        }
        animations[dir] = anim;
    }
    return true;
}