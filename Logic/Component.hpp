#pragma once
#include <eigen3/Eigen/Geometry>

namespace Logic
{

class Component
{
    Eigen::Vector2d pos_;
    double rotation_;

public:
Component();
void setPosition(const Eigen::Vector2d& pos);
void setRotation(const double& rotation);
Eigen::Vector2d getPosition();
double getRotation();

virtual ~Component() = 0; 
};


};