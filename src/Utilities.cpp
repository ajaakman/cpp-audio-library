#include "./Utilities.h"

namespace audio
{
	const float& Utilities::Clamp(const float& dValue, const float& dMin, const float& dMax) {
		if (dValue < dMin) return dMin;
		else if (dValue > dMax) return dMax;
		return dValue;
	};

	const float& Utilities::Lerp(float& dValue, const float& dTarget, const float& dSpeed, const float& dMin, const float& dMax)
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