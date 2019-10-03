#pragma once

namespace audio {
	class Utilities final
	{
	public:
		static const double& Clamp(const double& dValue, const double& dMin, const double& dMax);
		static const double& Lerp(double& dValue, const double& dTarget, const double& dSpeed, const double& dMin, const double& dMax);
	};
}