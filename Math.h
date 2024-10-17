#pragma once

#include <cmath>

namespace Math 
{
	inline double distance(float x, float y)
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}
}