#include "System.hpp"
#include "Utility.hpp"
#include <algorithm>
#include <utility>

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
        if(component != nullptr)
        {
            component->step();
        }
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
    std::vector<std::pair<double, std::shared_ptr<Component>>> ret;
    Eigen::Vector2d this_pos = self.getPosition();
    auto status = self.getStatus();
    fetchComponent();
    for(auto other : this->components_)
    {
        if(&self != other.get())
        {
            auto other_pos = other->getPosition();
            Eigen::Vector2d diff = this_pos - other_pos;
            double dist = diff.norm();
            double angle_diff = diff_deg(self.getRotation(), calcAngle(this_pos, other_pos)) ;
            if(dist < status.sight_distance && std::abs(angle_diff) < ( status.sight_angle / 2.0))
            {
                ret.push_back(std::make_pair(dist, other));
            }
        }
    }

    /* 距離が近い順に並び替える */
    std::sort(std::begin(ret), std::end(ret),
              [](const auto& a, const auto& b)->bool{ return a.first < b.first;});

    std::vector<std::shared_ptr<Component>> in_sight;
    std::transform(std::begin(ret), std::end(ret),
               std::back_inserter(in_sight),
               [](auto const& pair){ return pair.second; });

    return in_sight;
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
            if(dist < 500 && other->getType() == FOOD && component.getType() == PREY)
            {
                auto self_status = component.getStatus();
                self_status.energy += 1000;
                component.setStatus(self_status);
                Status food_status = component.getStatus();
                food_status.energy -= 100000; 
                other->setStatus(food_status);
            }

            if(dist < 500 && other->getType() == PREY && component.getType() == PREDATOR)
            {   
                auto self_status = component.getStatus();
                self_status.energy += 1000;
                component.setStatus(self_status);
                Status prey_status = component.getStatus();
                prey_status.energy -= 100000; 
                other->setStatus(prey_status);
            }
        }
    }
}

std::shared_ptr<Component> System::getComponent(const int& idx)
{
    return this->components_[idx];
}

};