#include "common.hpp"
float approach(const float &goal, const float &current, const float &dt)
{
    const float diff = goal - current;
    const bool bigger = diff > dt;
    const bool lesser = diff < -dt;
    return (bigger) * (current + dt) + (lesser) * (current - dt) + (!bigger && !lesser) * goal;
}
float remap(const float& value, const float& low1, const float& high1, const float& low2, const float& high2)
{
	float yellow = (value - low1) / (high1 - low1);
	float green = yellow * (high2 - low2) + low2;
    return green;
}