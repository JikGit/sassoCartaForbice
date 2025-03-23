#include "../include/Rect.hpp"
#include <iostream>


std::unordered_map<std::string, sf::Texture> Rect::textures;

Rect::Rect(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f vel, std::string type, sf::Color color) 
        : pos(pos), vel(vel), size(size), type(type) {
    this->body.setSize(size);
    this->body.setPosition(pos);

    setTextureFromType(this->type);
}

void Rect::loadTextures() {
    std::string types[] = {"sasso", "carta", "forbice"};
    
    for (const auto& type : types) {
        if (!textures[type].loadFromFile("src/img/" + type + ".png")) {
            std::cerr << "Errore: impossibile caricare src/img/" << type << ".png" << std::endl;
        }
    }
}

void Rect::setTextureFromType(const std::string& type) {
    auto it = textures.find(type);
    if (it != textures.end()) {
        this->body.setTexture(&it->second);  // ✅ Usa la texture già caricata
    } else {
        std::cerr << "Errore: texture non trovata per il tipo '" << type << "'" << std::endl;
    }
}

void Rect::render(sf::RenderWindow &window) {
    window.draw(this->body);
}

bool Rect::controllaHit(Rect &rect) {
    return this->pos.x < rect.pos.x + rect.size.x && this->pos.x + this->size.x > rect.pos.x
        && this->pos.y < rect.pos.y + rect.size.y && this->pos.y + this->size.y > rect.pos.y;
}

void Rect::fisicaCollisione(Rect &rect) {
    float x1 = this->pos.x, y1 = this->pos.y;
    float w1 = this->size.x, h1 = this->size.y;

    float x2 = rect.pos.x, y2 = rect.pos.y;
    float w2 = rect.size.x, h2 = rect.size.y;
    // Calcola la penetrazione in entrambe le direzioni
    float overlapX = std::min(x1 + w1, x2 + w2) - std::max(x1, x2);
    float overlapY = std::min(y1 + h1, y2 + h2) - std::max(y1, y2);

    // Spostiamo i rettangoli per evitare la sovrapposizione
    if (overlapX < overlapY) {
        // Collisione orizzontale
        if (this->pos.x < rect.pos.x) {
            this->pos.x -= overlapX / 2;
            rect.pos.x += overlapX / 2;
        } else {
            this->pos.x += overlapX / 2;
            rect.pos.x -= overlapX / 2;
        }

        std::swap(this->vel.x, rect.vel.x);
    } else {
        // Collisione verticale
        if (this->pos.y < rect.pos.y) {
            this->pos.y -= overlapY / 2;
            rect.pos.y += overlapY / 2;
        } else {
            this->pos.y += overlapY / 2;
            rect.pos.y -= overlapY / 2;
        }

        std::swap(this->vel.y, rect.vel.y);
    }
}

void Rect::aggiornaFisica(sf::Time dt) {
    if (this->pos.x >= WIDTH - this->size.x || this->pos.x <= 0)
        this->vel.x *= -1;
    if (this->pos.y >= HEIGHT - this->size.y || this->pos.y <= 0)
        this->vel.y *= -1;

    this->setPos(this->pos + this->vel * dt.asSeconds());
}

// Getters
sf::Vector2f Rect::getPos() { return this->pos; }
sf::Vector2f Rect::getVel() { return this->vel; }
std::string Rect::getType() { return this->type; }

// Setters
void Rect::setVel(float x, float y) { this->vel = {x, y}; }
void Rect::setPos(sf::Vector2f pos) {
    this->pos = pos;
    this->body.setPosition(this->pos);
}
