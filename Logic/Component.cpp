#include "Component.hpp"
#include "Utility.hpp"

namespace Logic {
Component::Component(COMPONENT_TYPE type) :
    pos_{0.0, 0.0}, rotation_(0.0), status_{60.0, 100, 10000}, type_(type), target_(std::nullopt)
{

}
void Component::setPosition(const Eigen::Vector2d& pos)
{
    this->pos_ = pos;
}

void Component::setRotation(const double& rotation)
{
    this->rotation_ = wrap_deg(rotation);
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

std::optional<Eigen::Vector2d> Component::getTarget()
{
    return this->target_;
}

void Component::setTarget(const std::optional<Eigen::Vector2d>& target)
{
    this->target_ = target;
}
};