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
public:
    System();
    void addComponent(std::shared_ptr<Component> component);
    void updatePos(std::shared_ptr<Component> component, const Eigen::Vector2d& position);
};

};