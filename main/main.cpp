#include "Logic.hpp"
#include <cstdlib>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include "ArcShape.hpp"
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>

void draw(sf::RenderWindow& window, std::shared_ptr<Logic::Component> component);

int main()
{
    boost::mt19937 gen;
    boost::random::uniform_int_distribution<> dist_x(0, 1000);
    boost::random::uniform_int_distribution<> dist_y(0, 500);
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode(1000, 500)), "Life");
    Logic::System system;
    for(int i = 0; i < 10; i++)
    {
        auto prey = std::make_shared<Logic::Prey>(&system);
        prey->setPosition(Eigen::Vector2d(dist_x(gen), dist_y(gen)));
        system.addComponent(prey);
    }

    for(int i = 0; i < 2; i++)
    {
        auto food = std::make_shared<Logic::Food>(&system);
        food->setPosition(Eigen::Vector2d(dist_x(gen), dist_y(gen)));
        system.addComponent(food);
    }
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
        std::function<void (const std::shared_ptr<Logic::Component> )> func = std::bind(draw, std::ref(window), std::placeholders::_1);
        system.eachComponent(func);
        system.step();
        window.display();
        sf::sleep(sf::milliseconds(5));
    }

    return EXIT_SUCCESS;
}

void draw(sf::RenderWindow& window, std::shared_ptr<Logic::Component> component)
{
    switch(component->getType())
    {
        case Logic::PREY : {
            auto target = component->getTarget();
            if(target)
            {
                sf::CircleShape marker(12);
                marker.setFillColor(sf::Color(255, 0, 0));
                marker.setPosition(target->x() - 6.0, target->y() - 6.0);
                window.draw(marker);
            }
            auto prey_pos = component->getPosition();
            auto status = component->getStatus();
            ArcShape sight(status.sight_angle, status.sight_distance);
            sf::CircleShape prey_body(10);

            sight.setPosition(prey_pos.x(), prey_pos.y());
            sight.setRotation(component->getRotation() + 90.0 - status.sight_angle / 2.0);
            sight.setFillColor(sf::Color(255, 255, 0, 100));

            prey_body.setPosition(prey_pos.x() - 10.0, prey_pos.y() - 10.0);

            window.draw(sight);
            window.draw(prey_body);
            break;
        }
        case Logic::FOOD : {
            auto food_pos = component->getPosition();
            sf::CircleShape food_body(10);
            food_body.setPosition(food_pos.x() - 10.0, food_pos.y() - 10.0);
            food_body.setFillColor(sf::Color(0, 255, 0));
            window.draw(food_body);
            break;
        }
    }
}