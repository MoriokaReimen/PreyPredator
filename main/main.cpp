#include "Logic.hpp"
#include <cstdlib>
#include <memory>
#include "Graphic.hpp"
#include <functional>

#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "Graphic.hpp"

int main()
{
    boost::mt19937 gen;
    boost::random::uniform_int_distribution<> dist_x(0, 1000);
    boost::random::uniform_int_distribution<> dist_y(0, 500);
    Graphic graphic;
    Logic::System system;
    for(int i = 0; i < 20; i++)
    {
        auto prey = std::make_shared<Logic::Prey>(&system);
        prey->setPosition(Eigen::Vector2d(dist_x(gen), dist_y(gen)));
        system.addComponent(prey);
    }
    for(int i = 0; i < 10; i++)
    {
        auto food = std::make_shared<Logic::Food>(&system);
        food->setPosition(Eigen::Vector2d(dist_x(gen), dist_y(gen)));
        system.addComponent(food);
    }
    for(int i = 0; i < 1; i++)
    {
        auto predator = std::make_shared<Logic::Predator>(&system);
        predator->setPosition(Eigen::Vector2d(dist_x(gen), dist_y(gen)));
        system.addComponent(predator);
    }
    // run the program as long as the window is open
    while (graphic.isOpen())
    {
        graphic.handleInput();
        graphic.draw(system);
        system.step();
        sf::sleep(sf::milliseconds(5));
    }

    return EXIT_SUCCESS;
}
