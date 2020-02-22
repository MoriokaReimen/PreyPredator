#pragma once
#include <eigen3/Eigen/Geometry>

double calcAngle(const Eigen::Vector2d& self, const Eigen::Vector2d& other);
double deg_to_rad(const double& angle);
double rad_to_deg(const double& angle);
double wrap_deg(const double& angle);
double wrap_rad(const double& angle);