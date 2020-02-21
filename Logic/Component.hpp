#pragma once
#include <eigen3/Eigen/Geometry>

namespace Logic
{

struct Status
{
    double sight_angle;
    double sight_distance;
    int energy;
};

enum COMPONENT_TYPE
{
    PREY,
    FOOD
};

class Component
{
    Eigen::Vector2d pos_;
    double rotation_;

protected:
    Status status_;
    COMPONENT_TYPE type_;
    std::optional<Eigen::Vector2d> target_;

public:
Component(COMPONENT_TYPE type);
void setPosition(const Eigen::Vector2d& pos);
void setRotation(const double& rotation);
Eigen::Vector2d getPosition();
double getRotation();
virtual void step() = 0;
virtual ~Component() {};
COMPONENT_TYPE getType();
Status getStatus() const;
void setStatus(const Status& status);
std::optional<Eigen::Vector2d> getTarget();
void setTarget(const std::optional<Eigen::Vector2d>& target);
};


};