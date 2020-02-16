#include "Logic.hpp"
#include <cstdlib>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
void draw(sf::RenderWindow& window, std::shared_ptr<Logic::Component> component);

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode(800, 600)), "Life");
    Logic::System system;
    auto prey = std::make_shared<Logic::Prey>(&system);
    system.addComponent(prey);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        window.clear();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        std::function<void (const std::shared_ptr<Logic::Component> )> func = std::bind(mydraw, std::ref(window), std::placeholders::_1);
        system.eachComponent(func);
        prey->step();
        window.display();
        sf::sleep(sf::milliseconds(5));
    }

    return EXIT_SUCCESS;
}

void draw(sf::RenderWindow& window, std::shared_ptr<Logic::Component> component)
{
    auto pos = component->getPosition();
    sf::CircleShape shape(10);
    shape.setPosition(pos.x(), pos.y());
    window.draw(shape);
}