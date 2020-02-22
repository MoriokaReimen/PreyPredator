#pragma once
#include "System.hpp"
#include "Component.hpp"
#include <boost/random/random_device.hpp>

namespace Logic
{
class Predator : public Component
{
    static boost::random_device gen_;
    System* system_;
public:
    Predator(System* system);
    void step();
};

};
