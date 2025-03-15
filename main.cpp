#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include <vector>

#include "constants.hpp"
#include "rettangolo.cpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "SFML Window",
                            sf::State::Fullscreen);
    std::vector<Rettangolo> insieme;

    for (int x = 0; x < 20; x++) {
        Rettangolo rect = Rettangolo({float(rand() % WIDTH), float(rand() % HEIGHT)}, {80,80}, {float(rand() % 200), float(rand() % 200)}, sf::Color::Red);
        insieme.push_back(rect);
    }

    /*Rettangolo rect = Rettangolo({300, 400}, {100, 100}, {100, 50}, sf::Color::Red);*/
    /*Rettangolo rect2 = Rettangolo({1200, 400}, {100, 100}, {-100, 50}, sf::Color::Red);*/
    /*insieme.push_back(rect);*/
    /*insieme.push_back(rect2);*/

    window.setFramerateLimit(FRAME_RATE);
    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();

        while (const std::optional event = window.pollEvent()) {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        for (int i = 0; i < insieme.size() -1; i++) {
            for (int x = i+1; x < insieme.size(); x++) {
                insieme[i].controllaHit(insieme[x]);
            }
        }


        for (Rettangolo &rect : insieme){
            rect.aggiornaFisica(dt);
        }

        // render
        window.clear(sf::Color::Black);

        for (Rettangolo& rect : insieme){
            rect.render(window);
        }

        window.display();
    }
};
