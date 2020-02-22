#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Logic.hpp"
#include "ArcShape.hpp"

class Graphic
{
    sf::RenderWindow window_;
    sf::Font font_;
    bool is_open_;
    void draw_debug(Logic::System& system);
    void draw_scene(std::shared_ptr<Logic::Component> component);
public:
    Graphic();
    void handleInput();
    void draw(Logic::System& system);
    bool isOpen();
};
