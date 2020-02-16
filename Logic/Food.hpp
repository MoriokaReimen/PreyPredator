#pragma once
#include "System.hpp"
#include "Component.hpp"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

namespace Logic
{
class Food : public Component
{
    static boost::mt19937 gen;
    static boost::random::uniform_int_distribution<> dist_x;
    static boost::random::uniform_int_distribution<> dist_y;
    int step_counter_;
    System* system_;
public:
    Food(System* system);
    void step();
};

};