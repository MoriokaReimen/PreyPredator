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
    double r_x = static_cast<double>(std::rand()) / RAND_MAX;
    double r_y = static_cast<double>(std::rand()) / RAND_MAX;
    pos += (2 * r_x  - 1) * Eigen::Vector2d::UnitX();
    pos += (2 * r_y  - 1) * Eigen::Vector2d::UnitY();
    system_->updatePos(*this, pos);

}


};