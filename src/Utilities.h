#pragma once

namespace audio {
	class Utilities final
	{
	public:
		static const float& lerp(float& dValue, const float& dTarget, const float& dSpeed, const float& dMin, const float& dMax);
	};
}