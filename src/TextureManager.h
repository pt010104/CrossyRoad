#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>

class TextureManager {
public:
    static sf::Texture& GetTexture(const std::string& filename) {
        static std::unordered_map<std::string, sf::Texture> textures;
        auto& tex = textures[filename];
        if (!tex.getNativeHandle()) { //check loading texture
            if (!tex.loadFromFile(filename)) {
                std::cerr << "Failed to load texture: " << filename << std::endl;
            }
        }
        return tex;
    }
};