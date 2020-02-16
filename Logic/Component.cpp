#include "Component.hpp"

namespace Logic {
Component::Component(COMPONENT_TYPE type) :
    pos_{0.0, 0.0}, rotation_(0.0), status_{10000}, type_(type)
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

COMPONENT_TYPE Component::getType()
{
    return type_;
}

Status Component::getStatus() const
{
    return status_;

}

void Component::setStatus(const Status& status)
{
    this->status_ = status;
}
};