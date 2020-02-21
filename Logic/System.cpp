#include "System.hpp"
#include <algorithm>

namespace Logic
{

System::System() : WIDTH(1000.0), HEIGHT(500.0)
{

}

void System::addComponent(std::shared_ptr<Component> component)
{
    this->buffer_.push_back(component);
}

void System::updatePos(Component& component, const Eigen::Vector2d& position)
{
    bool collide = false;
    fetchComponent();
    Status status = component.getStatus();
    status.collide = COLLIDE::NO_COLLIDE;

    for(auto other : this->components_)
    {
        if(&component != other.get())
        {

            auto other_pos = other->getPosition();
            auto diff = position - other_pos;
            double dist = diff.dot(diff);
            if(dist < 10)
            {
                collide = true;
                status.collide = COLLIDE::COMPONENT;
            }
        }
    }

    if(position.x() < 0 || position.x() > WIDTH)
    {
        collide = true;
    }

    if(position.y() < 0 || position.y() > HEIGHT)
    {
        collide = true;
    }

    if(!collide)
    {
        component.setPosition(position);
    } else {
        status.collide = COLLIDE::WALL;
    }

    component.setStatus(status);
}

void System::eachComponent(const std::function<void (const std::shared_ptr<Component> )>& func)
{
    fetchComponent();
    for(auto component : components_)
    {
        func(component);
    }
}

void System::step()
{
    fetchComponent();
    for(auto component : components_)
    {
        component->step();
    }
    this->reap();
}

void System::reap()
{
    fetchComponent();
    components_.erase(std::remove_if(components_.begin(), components_.end(),
                      [](const std::shared_ptr<Component>& x) {return x->getStatus().energy <= 0;})
                     , components_.end());
}

void System::fetchComponent()
{
    if(!buffer_.empty())
    {
        components_.insert(
        components_.end(),
        std::make_move_iterator(buffer_.begin()),
        std::make_move_iterator(buffer_.end())
        );
        buffer_.clear();
    }
}

std::vector<std::shared_ptr<Component>> System::getSight(Component& self)
{
    std::vector<std::shared_ptr<Component>> ret;
    Eigen::Vector2d this_pos = self.getPosition();
    auto status = self.getStatus();
    fetchComponent();
    for(auto other : this->components_)
    {
        if(&self != other.get())
        {
            auto other_pos = other->getPosition();
            auto diff = this_pos - other_pos;
            double dist = diff.norm();
            double other_angle = std::acos(diff.y() / diff.norm()) / M_PI * 180.0;
            auto normalized = std::remainder(other_angle, 360.0);
            double angle_diff =  std::remainder(self.getRotation() - normalized, 360.0);
            if(dist < status.sight_distance && std::abs(angle_diff) < status.sight_angle)
            {
                ret.push_back(other);
            }
        }
    }
    return ret;
}

void System::consume(Component& component)
{
    Eigen::Vector2d this_pos = component.getPosition();
    fetchComponent();
    for(auto other : this->components_)
    {
        if(&component != other.get())
        {

            auto other_pos = other->getPosition();
            auto diff = this_pos - other_pos;
            double dist = diff.dot(diff);
            if(dist < 500 && other->getType() == FOOD)
            {
                auto self_status = component.getStatus();
                self_status.energy += 1000;
                component.setStatus(self_status);
                Status food_status = component.getStatus();
                food_status.energy -= 100000; 
                other->setStatus(food_status);
            }
        }
    }
}
};