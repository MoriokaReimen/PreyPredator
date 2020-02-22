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

double wrap_deg_180(const double& angle)
{
    double wrapped = angle;
    wrapped -= 360.0 * std::floor((wrapped + 180.0) / 360.0);
    return wrapped;
}

double wrap_deg_360(const double& angle)
{
    double wrapped = std::fmod(angle, 360.0);

    if (wrapped < 0)
        wrapped += 360;
    return wrapped;
}

double wrap_rad_pi(const double& angle)
{
    double wrapped = rad_to_deg(angle);
    wrapped = wrap_deg_180(wrapped);
    return deg_to_rad(wrapped);
}

double wrap_rad_2pi(const double& angle)
{
    double wrapped = rad_to_deg(angle);
    wrapped = wrap_deg_360(wrapped);
    return deg_to_rad(wrapped);
}


double diff_deg(const double& self, const double& other)
{
    double wrapped_self = wrap_deg_360(self);
    double wrapped_other = wrap_deg_360(other);

    double diff = wrapped_other - wrapped_self;
    return wrap_deg_180(diff);
}