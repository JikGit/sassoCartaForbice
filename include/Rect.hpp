#ifndef RECT_HPP
#define RECT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <memory>
#include "constants.hpp"

class Rect {
private:
    sf::RectangleShape body;
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f size;
    std::string type;
    static std::unordered_map<std::string, sf::Texture> textures;



public:
    // Costruttore
    Rect(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f vel, std::string type, sf::Color color = sf::Color::Red);

    // Metodi
    void setTextureFromType(const std::string& type);
    void render(sf::RenderWindow &window);
    bool controllaHit(Rect &rect);
    void fisicaCollisione(Rect &rect);
    void aggiornaFisica(sf::Time dt);
    static void loadTextures();

    sf::Vector2f getPos();
    sf::Vector2f getVel();
    std::string getType();


    void setVel(float x, float y);
    void setPos(sf::Vector2f pos);
};

#endif
