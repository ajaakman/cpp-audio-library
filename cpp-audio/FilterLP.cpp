#include "FilterLP.h"
#include "Utilities.h"

namespace audio {

	FilterLP::FilterLP()
		: m_dPrevSample(0.0), m_dCutoff(20000.0)
	{}

	void FilterLP::CalcSample(double& dSample)
	{				
		for (int i = 0; i < 4; ++i)
		dSample = m_dPrevSample
			+ (1.0 / 44100.0 / (1.0 / (m_dCutoff * 2.0 * 3.14) + 1.0 / 44100.0) // TODO. Check that sample rate matches.
			* (dSample - m_dPrevSample));
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
