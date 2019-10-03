#include "./Utilities.h"

namespace audio {
	const double& Utilities::Clamp(const double& dValue, const double& dMin, const double& dMax) {
		if (dValue < dMin) return dMin;
		else if (dValue > dMax) return dMax;
		return dValue;
	};

	const double& Utilities::Lerp(double& dValue, const double& dTarget, const double& dSpeed, const double& dMin, const double& dMax)
	{
		// If the current value is not similar to the target value, add or subtract the factor.
		if (dValue < dTarget - dSpeed || dValue > dTarget + dSpeed)
			dValue += dValue < dTarget ? dSpeed : -dSpeed;
		else
			return dValue;
		// If the current value is close to the Min/Max round it up/down.
		if (dValue < dMin + dSpeed) return dMin;
		if (dValue > dMax - dSpeed) return dMax;
		return dValue;
	}
}