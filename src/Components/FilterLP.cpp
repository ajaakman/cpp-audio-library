#include "./FilterLP.h"
#include "../Utilities.h"

namespace audio {
	FilterLP::FilterLP(const MasterMixer& masterMixer)
		: Component(masterMixer)
        , m_prev_samples{ 0.0f }
        , m_cutoff(20000.0f)
	{ }

	void FilterLP::writeSamples(std::array<float, CHANNELS<size_t>>& samples)
	{
		for (size_t i = 0; i < samples.size(); i++)
		{
			for (unsigned j = 0; j < 4; ++j)
			{
				samples[i] = m_prev_samples[i]
					+ (1.0f / SAMPLE_RATE<float> / (1.0f / (m_cutoff * TWO_PI<float>) + 1.0f / SAMPLE_RATE<float>)
					* (samples[i] - m_prev_samples[i]));
			}
		}
		m_prev_samples = samples;
	}

	void FilterLP::setCutoff(const float new_cutoff)
	{
		m_cutoff = std::clamp(new_cutoff, 1.0f, 20000.0f);
	}

	const float FilterLP::getCutoff() const
	{
		return m_cutoff;
	}
}