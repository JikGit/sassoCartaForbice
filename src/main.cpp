#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <math.h>
#include <vector>

#include "../include/constants.hpp"
#include "../include/Rect.hpp"
#include "../include/GameLogic.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "SFML Window",
                sf::State::Fullscreen);
    window.setFramerateLimit(FRAME_RATE);
    sf::Clock deltaClock;

    std::vector<Rect> insieme;

    int numRect = 20;
    while (numRect >= 0) {
        Rect rect = Rect({float(rand() % WIDTH), float(rand() % HEIGHT)}, {100,100}, {float(rand() % 400), float(rand() % 400)}, "sasso");
        if (rand() % 3 == 0)
            rect = Rect({float(rand() % WIDTH), float(rand() % HEIGHT)}, {100,100}, {float(rand() % 400), float(rand() % 400)}, "carta");
        else if (rand() % 3 == 1)
            rect = Rect({float(rand() % WIDTH), float(rand() % HEIGHT)}, {100,100}, {float(rand() % 400), float(rand() % 400)}, "forbice");

        bool found = false;
        for (int i = 0; i < insieme.size(); i++)
            if (rect.controllaHit(insieme[i])) 
                found = true;

        if (!found) {
            numRect--;
            insieme.push_back(rect);
        }
    }

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        for (int i = 0; i < insieme.size() -1; i++) {
            for (int x = i+1; x < insieme.size(); x++) {
                if (insieme[i].controllaHit(insieme[x])) {
                    insieme[i].fisicaCollisione(insieme[x]);

                    int result = GameLogic::chiVinceContro(insieme[i], insieme[x]);

                    if (result == 1)
                        insieme.erase(insieme.begin() + x);
                    else if (result == 2)
                        insieme.erase(insieme.begin() + i);
                }
            }
        }


        for (Rect &rect : insieme)
            rect.aggiornaFisica(dt);

        // render
        window.clear(sf::Color::Black);

        for (Rect& rect : insieme)
            rect.render(window);

        window.display();
    }
};
