#pragma once

namespace acro {
	class Math
	{
	public:
		static float clamp(float num, float low, float high);
		static int clamp(int num, int low, int high);
	};
}