#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>

class TextureManager {
private:
    static std::map<std::string, sf::Texture> textures;

public:
    static sf::Texture& getTexture(const std::string& type);
};

