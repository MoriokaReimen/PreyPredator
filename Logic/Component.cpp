#include "Component.hpp"

namespace Logic {
Component::Component() :
    pos_{0.0, 0.0}, rotation_(0.0)
{

}
void Component::setPosition(const Eigen::Vector2d& pos)
{
    this->pos_ = pos;
}

void Component::setRotation(const double& rotation)
{
    this->rotation_ = rotation;
}

Eigen::Vector2d Component::getPosition()
{
    return this->pos_;
}

double Component::getRotation()
{
    return this->rotation_;
}


};