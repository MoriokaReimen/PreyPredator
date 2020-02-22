#pragma once
#include "System.hpp"
#include "Component.hpp"
#include <boost/random/random_device.hpp>

namespace Logic
{

class Prey : public Component
{
    static boost::random::random_device gen_;
    int run_timer_;
    Eigen::Vector2d last_spot_;
    System* system_;
    void randomWalk(std::vector<std::shared_ptr<Component>>& sight);
    void chaseFood(std::vector<std::shared_ptr<Component>>& sight);
    bool spotPredator(std::vector<std::shared_ptr<Component>>& sight);
    void run(std::vector<std::shared_ptr<Component>>& sight);
    bool is_matable(std::vector<std::shared_ptr<Component>>& sight);
    void chaseMate(std::vector<std::shared_ptr<Component>>& sight);
public:
    Prey(System* system);
    void step();
};

};
