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
    Eigen::Vector2d this_pos = component.getPosition();
    fetchComponent();
    for(auto other : this->components_)
    {
        if(&component != other.get())
        {

            auto other_pos = other->getPosition();
            auto diff = this_pos - other_pos;
            double dist = diff.dot(diff);
            if(dist < 100)
            {
                collide = true;
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
    }
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

};