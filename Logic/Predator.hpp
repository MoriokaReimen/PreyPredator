#pragma once
#include "System.hpp"
#include "Component.hpp"
#include <boost/random/mersenne_twister.hpp>

namespace Logic
{
class Predator : public Component
{
    static boost::mt19937 gen_;
    System* system_;
public:
    Predator(System* system);
    void step();
};

};
