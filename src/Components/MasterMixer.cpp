#include "./MasterMixer.h"

#include "../Utilities.h"

namespace audio
{
	MasterMixer::MasterMixer(double* const& dTime)
		: m_dAmpTarget(0.0f), m_dAmplitude(0.0f), m_bChannelClip(), m_bClipTimer()
	{
		m_dTime = dTime;
	}

	void MasterMixer::CalcSample(std::array<float, CHANNELS<size_t>>& dSample)
	{
		for (size_t i = 0; i < dSample.size(); ++i)
		{
			// Lerp the master amplitude before applying it to the final ouput to prevent audio clicks.
			dSample[i] *= Utilities::Lerp(m_dAmplitude, m_dAmpTarget, 0.0005f, 0.0f, 1.0f);

			SetChannelClip(i, dSample[i] > 1.0f ? true : false);
		}
	}

	void MasterMixer::SetChannelClip(size_t channel, bool value)
	{
		if (value)
		{
			m_bClipTimer[channel] = SAMPLE_RATE<unsigned>;
			m_bChannelClip[channel] = value;
		}
		else
		{
			if (!m_bClipTimer[channel])
			{
				m_bChannelClip[channel] = value;
			}
			else
			{
				--m_bClipTimer[channel];
			}
		}
	}

	const bool MasterMixer::SetOutput(Component* const& newOutput)
	{
		return false;
	}

	const Component* const MasterMixer::GetOutput() const
	{
		return nullptr;
	}

	const std::array<float, CHANNELS<size_t>>& MasterMixer::GetMasterOutput()
	{
		return FinalOutput();
	}

	const std::array<bool, CHANNELS<size_t>>& MasterMixer::IsOutClipping()
	{
		return m_bChannelClip;
	}

	void MasterMixer::SetAmplitude(const float& dNewAmplitude)
	{
		m_dAmpTarget = std::clamp(dNewAmplitude, 0.0f, 1.0f);
	}

	const float& MasterMixer::GetAmplitude()
	{
		return m_dAmpTarget;
	}
}