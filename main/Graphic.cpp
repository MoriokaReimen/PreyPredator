#include "Graphic.hpp"
#include <exception>
#include <boost/format.hpp>

Graphic::Graphic() :
    window_(sf::VideoMode(sf::VideoMode(1000, 500)), "Life"),
    is_open_(true)
{
    if(!font_.loadFromFile("resource/Sarai.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
}

void Graphic::handleInput()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
        {
            is_open_ = false;
            window_.close();
        }
    }
}

void Graphic::draw(Logic::System& system)
{
    window_.clear();
    std::function<void (const std::shared_ptr<Logic::Component> )> func =
            std::bind(&Graphic::draw_scene, this,  std::placeholders::_1);
    system.eachComponent(func);
    draw_debug(system);
    window_.display();

}

void Graphic::draw_scene(std::shared_ptr<Logic::Component> component)
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
                window_.draw(marker);
            }
            auto prey_pos = component->getPosition();
            auto status = component->getStatus();
            ArcShape sight(status.sight_angle, status.sight_distance);
            sf::CircleShape prey_body(10);

            sight.setPosition(prey_pos.x(), prey_pos.y());
            sight.setRotation(-component->getRotation() + 90.0 - status.sight_angle / 2.0);
            sight.setFillColor(sf::Color(255, 255, 0, 100));

            prey_body.setPosition(prey_pos.x() - 10.0, prey_pos.y() - 10.0);

            window_.draw(sight);
            window_.draw(prey_body);
            break;
        }
        case Logic::FOOD : {
            auto food_pos = component->getPosition();
            sf::CircleShape food_body(10);
            food_body.setPosition(food_pos.x() - 10.0, food_pos.y() - 10.0);
            food_body.setFillColor(sf::Color(0, 255, 0));
            window_.draw(food_body);
            break;
        }
    }
}

void Graphic::draw_debug(Logic::System& system)
{
    sf::Text text;
    auto component = system.getComponent(0);
    auto position = component->getPosition();
    auto rotation = component->getRotation();
    std::string message = (boost::format("X:%lf\nY:%lf\n") % position.x() % position.y()).str();
    message += (boost::format("R:%lf\n") % rotation).str();
    // select the font
    text.setFont(font_); // font is a sf::Font
    // set the string to display
    text.setString(message);
    // set the character size
    text.setCharacterSize(24); // in pixels, not points!
    // set the color
    text.setFillColor(sf::Color::White);
    // inside the main loop, between window.clear() and window.display()
    window_.draw(text);

}

bool Graphic::isOpen()
{
    return is_open_;
}