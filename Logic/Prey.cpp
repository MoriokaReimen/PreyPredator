#include "Prey.hpp"
#include <cstdlib>

namespace Logic {
Prey::Prey(System* system) :
    system_(system)
{

}

void Prey::step()
{
    auto pos = this->getPosition();
    pos += (std::rand() / RAND_MAX) * Eigen::Vector2d::UnitX();
    pos += (std::rand() / RAND_MAX) * Eigen::Vector2d::UnitY();
    system_->updatePos(*this, pos);

}


};