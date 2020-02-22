#include "Prey.hpp"
#include <cstdlib>
#include <boost/random/uniform_int_distribution.hpp>
#include <optional>
#include "Utility.hpp"

namespace Logic {
boost::random::random_device Prey::gen_;

Prey::Prey(System* system) :
    Component(PREY), run_timer_(-10), last_spot_{0.0, 0.0}, system_(system)
{

}

void Prey::step()
{
    auto sight = system_->getSight(*this);

    this->spotPredator(sight);
    if(run_timer_ > 0)
    {
        this->run(sight);
    }else if(is_matable(sight))
    {
        this->chaseMate(sight);
    }
    else if(!sight.empty() && sight[0]->getType() == FOOD)
    {
        this->chaseFood(sight);
    } else {
        this->randomWalk(sight);
    }

    system_->consume(*this);

}

void Prey::randomWalk(std::vector<std::shared_ptr<Component>>& sight)
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

void Prey::chaseFood(std::vector<std::shared_ptr<Component>>& sight)
{
    const double THRUST = 2.0;
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

bool Prey::spotPredator(std::vector<std::shared_ptr<Component>>& sight)
{
    bool ret = false;
    for(auto other : sight)
    {
        if(other->getType() == PREDATOR)
        {
            last_spot_ = other->getPosition();
            run_timer_ = 100;
            ret = true;
        }
    }

    return ret;
}

void Prey::run(std::vector<std::shared_ptr<Component>>& sight)
{
    const double THRUST = 3.0;
    auto pos = this->getPosition();
    auto rotation = this->getRotation();
    double angle = calcAngle(pos, last_spot_);
    double angle_diff =  diff_deg(rotation, angle) + 180;
    angle_diff = wrap_deg_180(angle_diff);
    rotation += angle_diff > 0 ? 10 : -10;

    this->setRotation(rotation);
    pos +=  THRUST * (Eigen::Rotation2D(-1.0 * deg_to_rad(this->getRotation())) * Eigen::Vector2d::UnitY());
    system_->updatePos(*this, pos);
    this->status_.energy -= THRUST;
    run_timer_ -= 1;
}

bool Prey::is_matable(std::vector<std::shared_ptr<Component>>& sight)
{
    bool self_condition = false;
    bool other_condition = false;

    auto self_status = this->getStatus();
    self_condition = self_status.energy > 3000;
    if(!sight.empty())
    {
        auto other_status = sight[0]->getStatus();
        other_condition = sight[0]->getType() == PREY && other_status.energy > 3000;
    }

    return self_condition && other_condition;
}
void Prey::chaseMate(std::vector<std::shared_ptr<Component>>& sight)
{
    const double THRUST = 2.0;
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

    auto dist = (pos - other_pos).norm();
    if(dist < 100 && is_matable(sight))
    {
        auto other_status = sight[0]->getStatus();
        auto self_status = this->getStatus();
        auto child = std::make_shared<Logic::Prey>(system_);
        child->setPosition(Eigen::Vector2d(pos.x(), pos.y()));
        system_->addComponent(child);
        other_status.energy = 1000;
        self_status.energy = 1000;
        this->setStatus(self_status);
        sight[0]->setStatus(other_status);
    }
}

};