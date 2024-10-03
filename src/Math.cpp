#include "Math.h"

namespace acro
{
	float Math::clamp(float num, float low, float high)
	{
		if (num <= low)
			return low;
		else if (num >= high)
			return high;
		else
			return num;
	}

	static int clamp(int num, int low, int high)
	{
		if (num <= low)
			return low;
		else if (num >= high)
			return high;
		else
			return num;
	}
}