#include "Math.h"


namespace acro
{
	float Math::clamp(float value, float min, float max)
	{
		if (min == max)
			return min;
		if (min > max) throw std::invalid_argument("min is greater than the max");
		if (max < min) throw std::invalid_argument("max is lesser than the min");
			
		if (value <= min)
			return min;
		else if (value >= max)
			return max;
		else
			return value;
	}

	int Math::clamp(int value, int min, int max)
	{
		if (min == max)
			return min;
		if (min > max) throw std::invalid_argument("min is greater than the max");
		if (max < min) throw std::invalid_argument("max is lesser than the min");

		if (value <= min)
			return min;
		else if (value >= max)
			return max;
		else
			return value;
	}



}