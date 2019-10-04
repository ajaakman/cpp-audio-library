#include "./FilterLP.h"
#include "../Utilities.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace audio {
	FilterLP::FilterLP()
		: m_dPrevSample(), m_dCutoff(20000.0)
	{}

	void FilterLP::CalcSample(std::array<double, CHANNELS>& dSample)
	{
		for (size_t i = 0; i < dSample.size(); i++)
		{
			for (unsigned j = 0; j < 4; ++j)
			{
				dSample[i] = m_dPrevSample[i]
					+ (1.0 / (double)SAMPLERATE / (1.0 / (m_dCutoff * 2.0 * M_PI) + 1.0 / (double)SAMPLERATE)
						* (dSample[i] - m_dPrevSample[i]));
			}
		}
		m_dPrevSample = dSample;
	}

	void FilterLP::SetCutoff(const double& dNewCutoff)
	{
		m_dCutoff = Utilities::Clamp(dNewCutoff, 1.0, 20000.0);
	}

	const double& FilterLP::GetCutoff() const
	{
		return m_dCutoff;
	}
}