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

TEST(Utility, test_wrap_deg_180)
{
    {
        double angle = wrap_deg_180(360);
        EXPECT_NEAR(angle, 0.0, 1E-6);
    }
    {
        double angle = wrap_deg_180(405);
        EXPECT_NEAR(angle, 45.0, 1E-6);
    }
    {
        double angle = wrap_deg_180(315);
        EXPECT_NEAR(angle, -45.0, 1E-6);
    }
    {
        double angle = wrap_deg_180(495);
        EXPECT_NEAR(angle, 135.0, 1E-6);
    }
    {
        double angle = wrap_deg_180(225);
        EXPECT_NEAR(angle, -135.0, 1E-6);
    }
}

TEST(Utility, test_angle_diff)
{
    {
        double diff = diff_deg(0, 45);
        EXPECT_NEAR(diff, 45, 1E-6);
    }
    {
        double diff = diff_deg(0, -45);
        EXPECT_NEAR(diff, -45, 1E-6);
    }
    {
        double diff = diff_deg(-45, -90);
        EXPECT_NEAR(diff, -45, 1E-6);
    }
    {
        double diff = diff_deg(-90, -45);
        EXPECT_NEAR(diff, 45, 1E-6);
    }
    {
        double diff = diff_deg(-90, -145);
        EXPECT_NEAR(diff, -55, 1E-6);
    }
}