#include <gtest/gtest.h>
#include <eigen3/Eigen/Geometry>
#include "Utility.hpp"

TEST(Utility, test_calcAngle)
{
    {
        Eigen::Vector2d self{1.0, 1.0};
        Eigen::Vector2d other(1.0, 2.0);
        double angle = calcAngle(self, other);
        EXPECT_NEAR(angle, 0.0, 1E-6);
    }
    {
        Eigen::Vector2d self{1.0, 1.0};
        Eigen::Vector2d other(2.0, 1.0);
        double angle = calcAngle(self, other);
        EXPECT_NEAR(angle, 90.0, 1E-6);
    }
    {
        Eigen::Vector2d self{1.0, 1.0};
        Eigen::Vector2d other(1.0, 0.0);
        double angle = calcAngle(self, other);
        EXPECT_NEAR(angle, 180.0, 1E-6);
    }
    {
        Eigen::Vector2d self{1.0, 1.0};
        Eigen::Vector2d other(0.0, 1.0);
        double angle = calcAngle(self, other);
        EXPECT_NEAR(angle, -90.0, 1E-6);
    }
    {
        Eigen::Vector2d self{1.0, 1.0};
        Eigen::Vector2d other(2.0, 2.0);
        double angle = calcAngle(self, other);
        EXPECT_NEAR(angle, 45.0, 1E-6);
    }
    {
        Eigen::Vector2d self{1.0, 1.0};
        Eigen::Vector2d other(2.0, 0.0);
        double angle = calcAngle(self, other);
        EXPECT_NEAR(angle, 135.0, 1E-6);
    }
    {
        Eigen::Vector2d self{1.0, 1.0};
        Eigen::Vector2d other(0.0, 0.0);
        double angle = calcAngle(self, other);
        EXPECT_NEAR(angle, -135.0, 1E-6);
    }
    {
        Eigen::Vector2d self{1.0, 1.0};
        Eigen::Vector2d other(0.0, 2.0);
        double angle = calcAngle(self, other);
        EXPECT_NEAR(angle, -45.0, 1E-6);
    }
}

TEST(Utility, test_wrap_deg)
{
    {
        double angle = wrap_deg(360);
        EXPECT_NEAR(angle, 0.0, 1E-6);
    }
    {
        double angle = wrap_deg(405);
        EXPECT_NEAR(angle, 45.0, 1E-6);
    }
    {
        double angle = wrap_deg(315);
        EXPECT_NEAR(angle, -45.0, 1E-6);
    }
    {
        double angle = wrap_deg(495);
        EXPECT_NEAR(angle, 135.0, 1E-6);
    }
    {
        double angle = wrap_deg(225);
        EXPECT_NEAR(angle, -135.0, 1E-6);
    }
}