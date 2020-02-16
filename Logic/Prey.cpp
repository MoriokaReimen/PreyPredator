#include "Prey.hpp"
#include <cstdlib>
#include <boost/random/uniform_int_distribution.hpp>

namespace Logic {
boost::mt19937 Prey::gen_;

Prey::Prey(System* system) :
    Component(PREY), system_(system)
{

}

void Prey::step()
{
    boost::random::uniform_int_distribution<> dist(-1, 1);

    auto pos = this->getPosition();
    auto rotation = this->getRotation();
    rotation += dist(gen_);
    this->setRotation(rotation);
    pos +=  Eigen::Rotation2D(this->getRotation()) * Eigen::Vector2d::UnitY();
    system_->updatePos(*this, pos);
    this->status_.energy -= 1;

}


};