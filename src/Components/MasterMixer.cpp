#include "./MasterMixer.h"

#include "../Utilities.h"
#include "../API.h"

namespace audio
{
	MasterMixer::MasterMixer(const double& time)
		: Component(*this), m_globalTime(time), m_amp_target(0.0f), m_amplitude(0.0f), m_channel_clip{ 0 }, m_clip_timer{ 0 }
	{
	}

	void MasterMixer::writeSamples(std::array<float, CHANNELS<size_t>>& samples)
	{
		for (size_t i = 0; i < samples.size(); ++i)
		{
			// Lerp the master amplitude before applying it to the final ouput to prevent audio clicks.
			samples[i] *= Utilities::lerp(m_amplitude, m_amp_target, (20.0f / SAMPLE_RATE<float>), 0.0f, 1.0f);

			setChannelClip(i, samples[i] > 1.0f ? true : false);
		}
	}

	void MasterMixer::setChannelClip(size_t channel, bool value)
	{
		if (value)
		{
			m_clip_timer[channel] = SAMPLE_RATE<unsigned>;
			if (!m_channel_clip[channel])
			{
				m_channel_clip[channel] = value;
				clipCallback(channel, true);
			}
		}
		else
		{
			if (m_clip_timer[channel])
			{
				--m_clip_timer[channel];
			}
			else
			{
				if (m_channel_clip[channel])
				{
					m_channel_clip[channel] = value;
					clipCallback(channel, false);
				}
			}
		}
	}

	const bool MasterMixer::setOutput(Component* const new_output)
	{
		return false;
	}

	const Component* const MasterMixer::getOutput() const
	{
		return nullptr;
	}

	const std::array<float, CHANNELS<size_t>>& MasterMixer::getMasterOutput()
	{
		return finalOutput();
	}

	const std::array<std::atomic<bool>, CHANNELS<size_t>>& MasterMixer::isOutClipping()
	{
		return m_channel_clip;
	}

	void MasterMixer::setAmplitude(const float new_amplitude)
	{
		m_amp_target = std::clamp(new_amplitude, 0.0f, 1.0f);
	}

	const float MasterMixer::getAmplitude()
	{
		return m_amp_target;
	}
}