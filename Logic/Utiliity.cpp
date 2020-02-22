#include "Utility.hpp"
#include <cmath>

double calcAngle(const Eigen::Vector2d& self, const Eigen::Vector2d& other)
{
    Eigen::Vector2d diff = other - self;
    diff.normalize();
    double angle{0.0};

    angle = std::atan2(diff.x(), diff.y());
    angle = rad_to_deg(angle);

    if(std::abs(diff.x()) < 1E-6)
    {
        angle = diff.y() > 0.0 ? 0.0 : 180.0;
    }

    return angle;
}

double deg_to_rad(const double& angle)
{
    return angle /180.0 * M_PI;
}

double rad_to_deg(const double& angle)
{
    return angle / M_PI * 180.0;
}

double wrap_deg(const double& angle)
{
    double wrapped = angle;
    wrapped -= 360.0 * std::floor((wrapped + 180.0) / 360.0);
    return wrapped;
}

double wrap_rad(const double& angle)
{
    double wrapped = rad_to_deg(angle);
    wrapped = wrap_deg(wrapped);
    return deg_to_rad(wrapped);
}