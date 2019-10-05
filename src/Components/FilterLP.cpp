#include "./FilterLP.h"
#include "../Utilities.h"

namespace audio {
	FilterLP::FilterLP()
		: m_dPrevSample(), m_dCutoff(20000.0f)
	{
		for (auto& sample : m_dPrevSample)
		{
			sample = 0.0f;
		}
	}

	void FilterLP::CalcSample(std::array<float, CHANNELS>& dSample)
	{
		for (size_t i = 0; i < dSample.size(); i++)
		{
			for (unsigned j = 0; j < 4; ++j)
			{
				dSample[i] = m_dPrevSample[i]
					+ (1.0f / (float)SAMPLERATE / (1.0f / (m_dCutoff * TWO_PI<float>) + 1.0f / (float)SAMPLERATE)
						* (dSample[i] - m_dPrevSample[i]));
			}
		}
		m_dPrevSample = dSample;
	}

	void FilterLP::SetCutoff(const float& dNewCutoff)
	{
		m_dCutoff = Utilities::Clamp(dNewCutoff, 1.0f, 20000.0f);
	}

	const float& FilterLP::GetCutoff() const
	{
		return m_dCutoff;
	}
}