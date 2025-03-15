#include "constants.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

class Rettangolo {
private:
    sf::RectangleShape body;
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f size;

public:
    Rettangolo(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f vel,
               sf::Color color = sf::Color::Red) {
        this->pos = pos;
        this->vel = vel;
        this->size = size;

        this->body.setSize(size);
        this->body.setFillColor(color);
        this->body.setPosition(pos);
    }

    void render(sf::RenderWindow &window) { window.draw(this->body); }

    bool controllaHit(Rettangolo &rect) {
        float x1 = this->pos.x, y1 = this->pos.y;
        float w1 = this->size.x, h1 = this->size.y;

        float x2 = rect.pos.x, y2 = rect.pos.y;
        float w2 = rect.size.x, h2 = rect.size.y;

        bool collisione = (x1 < x2 + w2 && x1 + w1 > x2 &&
            y1 < y2 + h2 && y1 + h1 > y2);

        if (collisione){ 
            kj


            return true;
        }
        return false;
    }

    void aggiornaFisica(sf::Time dt) {
        if (this->pos.x >= WIDTH - this->size.x || this->pos.x <= 0)
            this->vel.x *= -1;
        if (this->pos.y >= HEIGHT - this->size.y || this->pos.y <= 0)
            this->vel.y *= -1;

        this->setPos(this->pos + this->vel * dt.asSeconds());
    }

    sf::Vector2f getPos() { return this->pos; }

    sf::Vector2f getVel() { return this->vel; }

    void setVel(float x, float y) { this->vel = {x, y}; }

    void setPos(sf::Vector2f pos) {
        this->pos = pos;
        this->body.setPosition(this->pos);
    }
};
