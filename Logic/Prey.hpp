#pragma once
#include "System.hpp"
#include "Component.hpp"

namespace Logic
{
class Prey : public Component
{
    System* system_;
public:
    Prey(System* system);
    void step();
};

};