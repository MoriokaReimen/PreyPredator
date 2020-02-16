#include "Food.hpp"
#include <memory>

namespace Logic
{
boost::mt19937 Food::gen;
boost::random::uniform_int_distribution<> Food::dist_x(0, 1000);
boost::random::uniform_int_distribution<> Food::dist_y(0, 500);

Food::Food(System* system) :
    Component(FOOD), step_counter_{0}, system_(system)
{

}

void Food::step()
{
    if( step_counter_ > 100 )
    {
        auto food = std::make_shared<Logic::Food>(system_);
        food->setPosition(Eigen::Vector2d(dist_x(gen), dist_y(gen)));
        system_->addComponent(food);

    } else {
        step_counter_++;
    }
}

};