#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System.hpp>

class ArcShape : public sf::Shape
{
public :

    explicit ArcShape(double angle, double radius):
     radius_(radius), angle_(angle)
    {
        update();
    }

    void setRadius(const double& radius)
    {
        radius_ = radius;
        update();
    }

    const double& getRadius() const
    {
        return radius_;
    }

    void setAngle(const double& angle)
    {
        angle_ = angle;
        update();
    }

    const double& getAngle() const
    {
        return angle_;
    }

    virtual std::size_t getPointCount() const
    {
        return 30; // fixed, but could be an attribute of the class if needed
    }

    virtual sf::Vector2f getPoint(std::size_t index) const
    {
        if(index == 0) return sf::Vector2f(0.0, 0.0);

        static const float pi = 3.141592654f;

        float angle = index * (angle_ / getPointCount()) * pi / 180.0 ;
        float x = std::cos(angle) * radius_;
        float y = std::sin(angle) * radius_;

        return sf::Vector2f(x, y);
    }

private :
    double radius_;
    double angle_;
};