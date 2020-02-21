#include "Prey.hpp"
#include <cstdlib>
#include <boost/random/uniform_int_distribution.hpp>
#include <optional>

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
    auto in_sight = system_->getSight(*this);

    if(in_sight.empty() || in_sight[0]->getType() != FOOD)
    {
        rotation += 5 * dist(gen_);
        this->setTarget(std::nullopt);
    } else {
        auto other_pos = in_sight[0]->getPosition();
        this->setTarget(other_pos);
        auto diff = other_pos - pos;
        double normalized = std::acos(diff.y() / diff.norm()) / M_PI * 180.0;
        normalized -= 360.0 * std::floor((normalized + 180.) / 360.);
        double angle_diff =  normalized - this->getRotation();
        rotation += angle_diff > 0 ? -0.1 : 0.1;
    }

    /* 壁にぶつかったら反転する */
    if(this->status_.collide == WALL)
    {
        rotation += 180;
    }

    this->setRotation(rotation);
    pos +=  Eigen::Rotation2D(this->getRotation() / 180.0 * M_PI) * Eigen::Vector2d::UnitY();
    system_->updatePos(*this, pos);
    this->status_.energy -= 1;
    system_->consume(*this);

}


};