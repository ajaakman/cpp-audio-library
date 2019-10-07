#pragma once

namespace audio {
	class Utilities final
	{
	public:
		static const float& Lerp(float& dValue, const float& dTarget, const float& dSpeed, const float& dMin, const float& dMax);
	};
}