#include "Predator.hpp"
#include <cstdlib>
#include <boost/random/uniform_int_distribution.hpp>
#include <optional>
#include "Utility.hpp"

namespace Logic {
boost::random_device Predator::gen_;

Predator::Predator(System* system) :
    Component(PREDATOR), system_(system)
{

}

void Predator::step()
{
    auto sight = system_->getSight(*this);

    if(!sight.empty() && sight[0]->getType() == PREY)
    {
        this->chase(sight);
    } else {
        this->randomWalk(sight);
    }

    system_->consume(*this);

}

void Predator::randomWalk(std::vector<std::shared_ptr<Component>>& sight)
{
    boost::random::uniform_int_distribution<> dist(-1, 1);
    const double THRUST = 1.0;
    auto rotation = this->getRotation();
    auto pos = this->getPosition();
    rotation += 5 * dist(gen_);
    this->setTarget(std::nullopt);
    /* 壁にぶつかったら反転する */
    if(this->status_.collide == WALL)
    {
        rotation += 180;
    }
    this->setRotation(rotation);
    pos +=  Eigen::Rotation2D(-1.0 * THRUST * deg_to_rad(this->getRotation())) * Eigen::Vector2d::UnitY();
    system_->updatePos(*this, pos);
    this->status_.energy -= THRUST;
}

void Predator::chase(std::vector<std::shared_ptr<Component>>& sight)
{
    const double THRUST = 4.0;
    auto pos = this->getPosition();
    auto rotation = this->getRotation();
    auto other_pos = sight[0]->getPosition();
    double angle = calcAngle(pos, other_pos);
    double angle_diff =  diff_deg(rotation, angle);
    rotation += angle_diff > 0 ? 1 : -1;

    this->setTarget(other_pos);
    this->setRotation(rotation);
    pos +=  THRUST * (Eigen::Rotation2D(-1.0 * deg_to_rad(this->getRotation())) * Eigen::Vector2d::UnitY());
    system_->updatePos(*this, pos);
    this->status_.energy -= THRUST;
}

};