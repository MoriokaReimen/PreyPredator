#pragma once
#include <memory>
#include <vector>
#include "Component.hpp"
#include <functional>

namespace Logic
{

class System
{
    const double WIDTH;
    const double HEIGHT;
    std::vector<std::shared_ptr<Component>> components_;
    std::vector<std::shared_ptr<Component>> buffer_;
    void fetchComponent();
public:
    System();
    void addComponent(std::shared_ptr<Component> component);
    void updatePos(Component& component, const Eigen::Vector2d& position);
    void eachComponent(const std::function<void (const std::shared_ptr<Component> )>& func);
    void step();
    void reap();
    void consume(Component& component);
    std::vector<std::shared_ptr<Component>> getSight( Component& self);
    std::shared_ptr<Component> getComponent(const int& idx);
};

};